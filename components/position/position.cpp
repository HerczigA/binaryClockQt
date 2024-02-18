#include "position.h"
#include "moc_position.cpp"

const int getPosPeriod = 5000;

Position::Position(QObject *parent)
    : QObject{parent}
{
    mServiceProvider = make_unique<QGeoServiceProvider>("osm");
    mGeoManager = mServiceProvider->geocodingManager();
    if(mGeoManager)
    {
        qInfo() << QGeoPositionInfoSource::availableSources();

        mGeoPos = QGeoPositionInfoSource::createSource("geoclue2",this);
        if(mGeoPos)
        {
            mGeoPos->setPreferredPositioningMethods(QGeoPositionInfoSource::NonSatellitePositioningMethods);
            mConnections.push_back(connect(mGeoPos, &QGeoPositionInfoSource::positionUpdated, this, &Position::newPositionReceived));
            mConnections.push_back(connect(mGeoPos, &QGeoPositionInfoSource::errorOccurred, this, &Position::errorReceived));
            mConnections.push_back(connect(mGeoManager, &QGeoCodingManager::finished, this, &Position::getLocals));
//            mConnections.push_back(connect(mGeoCodeReply, SIGNAL(QGeoCodeReply::error(QGeoCodeReply::Error, const QString &)), this, SLOT(Position::localisationError(QGeoCodeReply::Error, const QString &))));

            mGeoPos->setUpdateInterval(getPosPeriod);
            mGeoPos->startUpdates();
            qInfo()<<"GeoPos started";
        }
        else
            qInfo()<< "No goemanager";
    }
    else
        qInfo()<<"Failed create goe Manager" << mServiceProvider->errorString();

}

Position::Position(Properties props, QObject *parent)
    : QObject{parent}
{
    mProps = make_unique<PositionProps>(props);
    emit requestLocation(mProps.get(), MainAppComponents::Types::Position);
}

Position::~Position()
{
    for(auto &con : mConnections)
        disconnect(con);
    if(mGeoPos)
        delete mGeoPos;

}

void Position::newPositionReceived(const QGeoPositionInfo &newPos)
{
    if(newPos.isValid())
    {
        qInfo()<< newPos.coordinate();

        mGeoCodeReply = mGeoManager->reverseGeocode(newPos.coordinate());
    }
}

void Position::newOnlinePositionReceived(MainAppComponents::PropertiesPacket packet)
{
    if (packet.type != MainAppComponents::Types::Position)
        return;

    QString newValue;
    for(auto key : packet.props.keys())
    {
        newValue = packet.props.value(key).toString();
        if(key == "city")
        {
            emit sendCity(newValue);
        }
    }
}

void Position::getLocals(QGeoCodeReply *reply)
{
    if(mGeoCodeReply != reply)
        mGeoCodeReply = reply;

    QList<QGeoLocation> loc = mGeoCodeReply->locations();
    if(loc.size() != 0)
    {
        mLocation = loc[0];

        if(!mLocation.isEmpty())
        {

            auto newaddress = mLocation.address();
            emit sendCity(newaddress.city());
        }
    }
}

void Position::localisationError(QGeoCodeReply::Error error, const QString &errorString)
{
    qInfo()<< "error occured when tried to get localisation\n " << errorString;
}

void Position::requestedLocation()
{
    emit requestLocation(mProps.get(), MainAppComponents::Types::Position);
}



void Position::errorReceived(QGeoPositionInfoSource::Error error)
{
    qInfo()<< "Error occurred when requested position"<< error;
    qInfo()<< "Maybe agent does not work"<< error;
}

void Position::errorGeoCodeManager()
{

}

Position::PositionProps::~PositionProps()
{

}

const QString Position::PositionProps::getRawUrl()
{
    QString url = mProps["url"].toString();
    QString key = "access_key=" +mProps["apikey"].toString();
    QString query = "&query=";
    return url + key + query;
}
