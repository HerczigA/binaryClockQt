#include "position.h"

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>

#include <QTimer>

#include <QDBusReply>
#include <QDBusVariant>

#include <memory>

constexpr int positionRequestInterval = 5000;
const QString desktopId("AviCado");

PositionRequestPackage::PositionRequestPackage(QObject *parent)
    :NetworkRequestPackage(parent)
{

}

PositionRequestPackage::~PositionRequestPackage()
{
}

void PositionRequestPackage::createUrl(const QSharedPointer<QVariant> data)
{
    QString rawUrl;
    if(data->canConvert<ConfigMap>())
    {
        ConfigMap configMap = data->toMap();
        QString url = configMap["url"].toString();
        QString key = "access_key=" +configMap["apikey"].toString();
        QString query = "&query="+ Network::parseIPv6();
        rawUrl = url+key+query;
        setRawUrl(rawUrl);
    }
}

Position::Position(QObject *parent)
    : QObject{parent}
    , mResourceType(PositionResources::Unknown)
{

    mServiceProvider = std::make_unique<QGeoServiceProvider>("osm");
    if(mServiceProvider)
    {
        // maybe use without unique ptr and call  delete later for this shit if necessary
        mGeoManager = mServiceProvider->geocodingManager();
        if(mGeoManager)
        {
            mGeoPos->setPreferredPositioningMethods(QGeoPositionInfoSource::NonSatellitePositioningMethods);
        }
        else
        {
            qDebug() << "Failed to create GeoManager";    
        }
    }
    else
    {
        qDebug() << "Failed to create OSM GeoServiceProvider";
    }
    
}


void Position::receivedConfig(const std::shared_ptr<Config::ConfigPacket> packet)
{
    if(packet->mConfigType == Config::Types::Position)
    {
        Config::parseEnumStringToKey<Position::PositionResources>(mResourceType, packet->mConfigMap["type"].toString());
        switch (mResourceType)
        {
        case Position::PositionResources::Plugin:
            createPluginClient();
            break;
        case Position::PositionResources::Dbus:
            createDBusClient();
            break;

        case Position::PositionResources::Online:
            mPositionRequestPackage = QSharedPointer<PositionRequestPackage>::create(this);
            mPositionRequestPackage->createUrl(QSharedPointer<QVariant>::create(QVariant(packet->mConfigMap)));
            mPositionRequestPackage->setOperationType(std::move(QNetworkAccessManager::Operation::GetOperation));
            break;
        
        default:
            break;
        }
        startLocationUpdate();
    }
}

Position::~Position()
{
    if (mGeoClueClientInterface) {
        mGeoClueClientInterface->call("Stop");
    }
    if(mGeoManager)
    {
        delete mGeoManager;
    }
}

void Position::newPositionReceived(const QGeoPositionInfo &newPos)
{
    if(newPos.isValid())
    {
        qInfo()<< newPos.coordinate();

        QGeoCodeReply* reply = mGeoManager->reverseGeocode(newPos.coordinate());
        connect(reply, &QGeoCodeReply::finished, this, [reply, this]() {
            if (reply->error() == QGeoCodeReply::NoError) {
                QList<QGeoLocation> loc = reply->locations();
                if(loc.size() != 0)
                {
                    if(!loc[0].isEmpty())
                    {
                        mGeoLocation = loc[0];
                        QString cityLocation = mGeoLocation.address().city();
                        emit sendLocation(cityLocation);
                    }
                }
            } else {
                qDebug()<< "Error occured in reversing GeoCode. Error reason: " << reply->errorString();
            }
        });
        reply->deleteLater();
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

void Position::requestedLocation()
{
    startLocationUpdate();
}

void Position::startLocationUpdate()
{
    switch (mResourceType)
    {
    case Position::PositionResources::Plugin:
        if(mGeoPos)
        {
            mGeoPos->requestUpdate(positionRequestInterval);
        }
        break;
    case Position::PositionResources::Dbus:
        /* code */
        break;
    case Position::PositionResources::Online:
        emit requestPackage(mPositionRequestPackage);
        break;
    case Position::PositionResources::GpsDevice:
        /* code */
        break;
    default:
        break;
    }
}

void Position::handleLocationUpdated(const QDBusObjectPath &oldPath, const QDBusObjectPath &newPath)
{

    qDebug() << "Location updated!";
    
    QDBusInterface locationInterface("org.freedesktop.GeoClue2",
                                     newPath.path(),
                                     "org.freedesktop.GeoClue2.Location",
                                     QDBusConnection::systemBus());
    if (!locationInterface.isValid()) {
        qDebug() << "Failed to create location interface due to:" << locationInterface.lastError().message();
        return;
    }

    
    double latitude = locationInterface.property("Latitude").toDouble();
    double longitude = locationInterface.property("Longitude").toDouble();
    

    qDebug() << "New location:";
    qDebug() << "Latitude:" << latitude;
    qDebug() << "Longitude:" << longitude;
}

void Position::createDBusClient()
{
     mGeoClueManagerInterface = new QDBusInterface("org.freedesktop.GeoClue2",
                                           "/org/freedesktop/GeoClue2/Manager",
                                           "org.freedesktop.GeoClue2.Manager",
                                           QDBusConnection::systemBus());
    if(mGeoClueManagerInterface->isValid())
    {
        QDBusReply<QDBusObjectPath> reply = mGeoClueManagerInterface->call("CreateClient");
        if (reply.isValid()) {
            mClientPath = reply.value().path();
            if(mClientPath.isEmpty())
                return;
            mGeoClueClientInterface = new QDBusInterface("org.freedesktop.GeoClue2", 
                                                    mClientPath,
                                                    "org.freedesktop.GeoClue2.Client",
                                                    QDBusConnection::systemBus());
            if(mGeoClueClientInterface->isValid())
            {
                bool success = mGeoClueClientInterface->setProperty("DesktopId", QVariant(desktopId));
                if (success) {
                    if(QVariant activeStatus = mGeoClueClientInterface->property("Active"); activeStatus.toBool())
                    {
                        // <signal name=\"LocationUpdated\">\n      <arg type=\"o\" name=\"old\"/>\n      <arg type=\"o\" name=\"new\"/>\n    </signal>\n
                        connect(mGeoClueClientInterface, SIGNAL(LocationUpdated(QDBusObjectPath, QDBusObjectPath)),this, SLOT(handleLocationUpdated(QDBusObjectPath, QDBusObjectPath)));
                    }
                    else
                    {
                        qDebug() << "interface is not active";
                    }
                    
                    QDBusReply<void> startReply = mGeoClueClientInterface->call("Start");
                    if (!startReply.isValid()) {
                        qDebug() << "Failed to call \"Start\" by client:" << startReply.error().message();
                    } 
                } 
                else 
                {
                    qDebug() << "Failed to set DesktopId";
                }
            }
            else
            {
                qDebug() << "Failed to create GeoClue2 Client interface";
            }
        } 
        else 
        {
            qDebug() << "Failed to get GeoClue2 client:" << reply.error().message();
        }
    }
    else
    {
        qDebug()<<"Failed to create GeoClue2 Manager interface";
    }
}

void Position::createPluginClient()
{
        QVariantMap params;
        params["desktopId"] = "AviCado";
        mGeoPos = QGeoPositionInfoSource::createSource("geoclue2", params, this);
        if(mGeoPos)
        {
            mGeoPos->setPreferredPositioningMethods(QGeoPositionInfoSource::NonSatellitePositioningMethods);
            connect(mGeoPos, &QGeoPositionInfoSource::positionUpdated, this, &Position::newPositionReceived);
            connect(mGeoPos, &QGeoPositionInfoSource::errorOccurred, this, [](QGeoPositionInfoSource::Error error)
            {
                qDebug() << "Error occured when plugin tried to request update. Error reason: " << Config::parseEnumKeyToString<QGeoPositionInfoSource::Error>(error);
            });
            
        }
        else
            qInfo()<< "No geoPos";
}

void Position::createNetworkRequest()
{

}
