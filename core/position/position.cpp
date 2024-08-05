#include "position.h"

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>

const int getPosPeriod = 5000;

PositionRequestPackage::PositionRequestPackage(QObject *parent)
    :NetworkRequestPackage(parent)
{

}

PositionRequestPackage::~PositionRequestPackage()
{
}

void PositionRequestPackage::createUrl(const QSharedPointer<QVariant> data)
{

    if(data->canConvert<ConfigMap>())
    {
        ConfigMap configMap = data->toMap();
        QString url = configMap["url"].toString();
        QString key = "access_key=" +configMap["apikey"].toString();
        QString query = "&query="+ Network::parseIPv6();
        setRawUrl(url+key+query);
    }
}

Position::Position(QObject *parent)
    : QObject{parent}
{
    mServiceProvider = std::make_unique<QGeoServiceProvider>("osm");
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


//    emit requestLocation(mProps.get(), MainAppComponents::Types::Position);
}

Position::Position(const ConfigMap &configMap)
{
    mPositionRequestPackage = QSharedPointer<PositionRequestPackage>::create();
    mPositionRequestPackage->createUrl(QSharedPointer<QVariant>::create(QVariant(configMap)));
    mPositionRequestPackage->setOperationType(std::move(QNetworkAccessManager::Operation::GetOperation));
    emit requestPackage(mPositionRequestPackage);
}

Position::~Position()
{
    for(auto &con : mConnections)
        disconnect(con);
    // if(mGeoPos)
    //     delete mGeoPos;

}

void Position::newPositionReceived(const QGeoPositionInfo &newPos)
{
    if(newPos.isValid())
    {
        qInfo()<< newPos.coordinate();

        mGeoCodeReply = mGeoManager->reverseGeocode(newPos.coordinate());
    }
}

void Position::newOnlinePositionReceived(const QByteArray& rawData)
{
    if(rawData.contains("locality"))
    {
        QJsonParseError result;
        QJsonDocument document = QJsonDocument::fromJson(rawData, &result);
        if(result.error == QJsonParseError::NoError && !document.isEmpty())
        {
            if(document.isObject())
            {
                QJsonObject object;
                object = document.object();
                if(!object.isEmpty())
                {
                    QJsonValue value = object.value("data");
                    if(!value.isNull())
                    {
                        emit sendLocation(value[0]["locality"].toVariant().toString());
                        
                    }
                }
            }
        }
        else
        {
            qInfo()<< "Error at json parsing object side";
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
            emit sendLocation(newaddress.city());
        }
    }
}

void Position::localisationError(QGeoCodeReply::Error error, const QString &errorString)
{
    qInfo()<< "error occured when tried to get localisation\n " << errorString;
}

void Position::requestedLocation()
{
    emit requestPackage(mPositionRequestPackage);
}


void Position::errorReceived(QGeoPositionInfoSource::Error error)
{
    qInfo()<< "Error occurred when requested position"<< error;
    qInfo()<< "Maybe agent does not work"<< error;
}

void Position::errorGeoCodeManager()
{

}


