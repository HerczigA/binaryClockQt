#include "position.h"

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>

#include <QTimer>

#include <QDBusReply>
#include <QDBusVariant>

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

    createPluginClient();
    //  m_geoClueManagerInterface = new QDBusInterface("org.freedesktop.GeoClue2",
    //                                        "/org/freedesktop/GeoClue2/Manager",
    //                                        "org.freedesktop.GeoClue2.Manager",
    //                                        QDBusConnection::systemBus());
}


void Position::receivedConfig(const std::shared_ptr<Config::ConfigPacket> packet)
{

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
    if (mGeoClueClientInterface) {
        mGeoClueClientInterface->call("Stop");
    }
    
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

        // mGeoCodeReply = mGeoManager->reverseGeocode(newPos.coordinate());
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
    // if(mGeoCodeReply != reply)
    //     mGeoCodeReply = reply;

    // QList<QGeoLocation> loc = mGeoCodeReply->locations();
    // if(loc.size() != 0)
    // {
    //     mLocation = loc[0];

    //     if(!mLocation.isEmpty())
    //     {

    //         auto newaddress = mLocation.address();
    //         emit sendLocation(newaddress.city());
    //     }
    // }
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





void Position::startLocationUpdate()
{
    if(m_geoClueManagerInterface->isValid())
    {

        QDBusReply<QDBusObjectPath> reply = m_geoClueManagerInterface->call("CreateClient");
        if (reply.isValid()) {
            m_clientPath = reply.value().path();
            if(m_clientPath.isEmpty())
                return;
            mGeoClueClientInterface = new QDBusInterface("org.freedesktop.GeoClue2", 
                                                    m_clientPath,
                                                    "org.freedesktop.GeoClue2.Client",
                                                    QDBusConnection::systemBus());
            if(mGeoClueClientInterface->isValid())
            {

                QVariant desktopId = "AviCado";
                bool success = mGeoClueClientInterface->setProperty("DesktopId", desktopId);
                if (success) {
                    qDebug() << "DesktopId set successfully";
                    success = mGeoClueClientInterface->setProperty("RequestedAccuracyLevel", QVariant::fromValue(5));
                    if(!success)
                    {
                        qDebug()<< "could not set accuracy level";
                        return;
                    }

                    if(QVariant activeStatus = mGeoClueClientInterface->property("Active"); activeStatus.toBool())
                    {

                        qDebug() << "interface is active";
                        QVariant location = mGeoClueClientInterface->property("Location");
                        if( location.isValid())
                        {
                            qDebug()<< "location is valid " << location.toString();
                        }

                    }
                    else
                    {
                        qDebug() << "interface is not active";
                    }
                     // <signal name=\"LocationUpdated\">\n      <arg type=\"o\" name=\"old\"/>\n      <arg type=\"o\" name=\"new\"/>\n    </signal>\n
                    connect(mGeoClueClientInterface, SIGNAL(LocationUpdated(QDBusObjectPath, QDBusObjectPath)),this, SLOT(handleLocationUpdated(QDBusObjectPath, QDBusObjectPath)));
                    QDBusReply<void> startReply = mGeoClueClientInterface->call("Start");
                    if (startReply.isValid()) {
                        qDebug() << "Client started successfully";
                        if(QVariant activeStatus = mGeoClueClientInterface->property("Active"); activeStatus.toBool())
                        {
                            qDebug() << "is active";
                        }
                        // Wait for a few seconds
                        // QTimer::singleShot(3000, this, [ this]() {
                        //     // Check if the client is active
                        //     bool isActive = mGeoClueClientInterface->property("Active").toBool();
                        //     if (isActive) {
                        //         qDebug() << "Location client is active, ready for updates";
                        //         // You can request an initial location here if you want
                        //         QVariant locationVariant = mGeoClueClientInterface->property("Location");
                        //         if (locationVariant.isValid()) {
                        //             QDBusObjectPath locationPath = qvariant_cast<QDBusObjectPath>(locationVariant);
                        //             if (!locationPath.path().isEmpty()) {
                        //                 handleLocationUpdated(QDBusObjectPath("/"), locationPath);  // Pass an empty old path
                        //             } else {
                        //                 qDebug() << "Location path is empty";
                        //             }
                        //         } else {
                        //             qDebug() << "Failed to get Location property";
                        //         }
                        //     } else {
                        //         qDebug() << "Location client is not active after startup";
                        //         // Handle the case where the client couldn't become active
                        //     }
                        // });
                    } else {
                        qDebug() << "Failed to start client:" << startReply.error().message();
                    }

                    connect(mGeoClueClientInterface, SIGNAL(LocationUpdated(QDBusObjectPath,QDBusObjectPath)),
                            this, SLOT(handleLocationUpdated(QDBusObjectPath,QDBusObjectPath)));
                        // You can now use this path to get the location data as shown in the handleLocationUpdated method

                } else {
                    qDebug() << "Failed to set DesktopId";
                }


            }
        } else {
            qDebug() << "Failed to get GeoClue2 client:" << reply.error().message();
        }
    }
}

void Position::handleLocationUpdated(const QDBusObjectPath &oldPath, const QDBusObjectPath &newPath)
{

    qDebug() << "Location updated!";
    qDebug() << "Old path:" << oldPath.path();
    qDebug() << "New path:" << newPath.path();

    // Now, let's get the actual location data
    QDBusInterface locationInterface("org.freedesktop.GeoClue2",
                                     newPath.path(),
                                     "org.freedesktop.GeoClue2.Location",
                                     QDBusConnection::systemBus());
    if (!locationInterface.isValid()) {
        qDebug() << "Failed to create location interface:" << locationInterface.lastError().message();
        return;
    }

    QDBusReply<QVariantMap> propsReply = locationInterface.call("GetAll", "org.freedesktop.GeoClue2.Location");
    if (propsReply.isValid()) {
        QVariantMap props = propsReply.value();
        qDebug() << "All location properties:" << props;
    } else {
        qDebug() << "Failed to get all properties:" << propsReply.error().message();
    }

    double latitude = locationInterface.property("Latitude").toDouble();
    double longitude = locationInterface.property("Longitude").toDouble();
    double accuracy = locationInterface.property("Accuracy").toDouble();

    qDebug() << "New location:";
    qDebug() << "Latitude:" << latitude;
    qDebug() << "Longitude:" << longitude;
    qDebug() << "Accuracy:" << accuracy << "meters";
}

void Position::handleLocationUpdated(QString oldPath, QString newPath)
{
    qDebug() << "Location updated!";
    qDebug() << "oldPath:" << oldPath;
    qDebug() << "newPath:" << newPath;


    // Now, let's get the actual location data
    
}

void Position::createPluginClient()
{
    qDebug()<< "Available QGeoServiceProvides: " << QGeoServiceProvider::availableServiceProviders();
        qDebug()<< "Available GeoPositionInfoSources: " << QGeoPositionInfoSource::availableSources();
        QVariantMap params;
        params["desktopId"] = "AviCado";
        // mGeoPos = QGeoPositionInfoSource::createSource("geoclue2", params, this);
        mGeoPos = QGeoPositionInfoSource::createSource("geoclue2", this);
        // mGeoPos = QGeoPositionInfoSource::createDefaultSource(params, this);
        
        if(mGeoPos)
        {
            qInfo()<< mGeoPos->error();
            mGeoPos->setPreferredPositioningMethods(QGeoPositionInfoSource::NonSatellitePositioningMethods);
            mConnections.push_back(connect(mGeoPos, &QGeoPositionInfoSource::positionUpdated, this, [](const QGeoPositionInfo& newPos){
                
                if(newPos.isValid())
                {
                    qInfo()<< "longitude: " <<  newPos.coordinate().longitude();
                    qInfo()<< "latitude: " <<  newPos.coordinate().latitude();

                }
                else{
                    qInfo()<< "not valid newPos";
                }
            }));
            //&Position::newPositionReceived));
            mConnections.push_back(connect(mGeoPos, &QGeoPositionInfoSource::errorOccurred, this, &Position::errorReceived));
            //mConnections.push_back(connect(mGeoManager, &QGeoCodingManager::finished, this, &Position::getLocals));
            //            mConnections.push_back(connect(mGeoCodeReply, SIGNAL(QGeoCodeReply::error(QGeoCodeReply::Error, const QString &)), this, SLOT(Position::localisationError(QGeoCodeReply::Error, const QString &))));

            mGeoPos->setUpdateInterval(getPosPeriod);
            mGeoPos->startUpdates();
            qInfo()<<"GeoPos started";
        }
        else
            qInfo()<< "No geoPos";
}
