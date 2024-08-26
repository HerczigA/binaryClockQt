#include "position.h"

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>

#include <QDBusReply>
#include <QDBusVariant>

namespace position
{

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
    , mResourceType(ResourceTypes::Unknown)
{

    mServiceProvider = std::make_unique<QGeoServiceProvider>("osm");
    if(mServiceProvider)
    {
        mGeoManager = mServiceProvider->geocodingManager();
        if(!mGeoManager)
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
        mPositionResource.reset();
        mResourceType = Config::parseEnumStringToKey<Position::ResourceTypes>(packet->mConfigMap["type"].toString());
        switch (mResourceType)
        {
        case Position::ResourceTypes::Plugin:
            mPositionResource = QSharedPointer<PositionPluginResource>::create();
            break;
        case Position::ResourceTypes::Dbus:
            mPositionResource = QSharedPointer<PositionDBusResource>::create();
            break;
        case Position::ResourceTypes::GpsDevice:
            // to do:  implement in the future if device will be available
            break;
        case Position::ResourceTypes::Online:
            // to do :move entire prop to position network class 
            // mPositionRequestPackage = QSharedPointer<PositionRequestPackage>::create(this);
            // mPositionRequestPackage->createUrl(QSharedPointer<QVariant>::create(QVariant(packet->mConfigMap)));
            // mPositionRequestPackage->setOperationType(std::move(QNetworkAccessManager::Operation::GetOperation));
            break;
        
        default:
            break;
        }
        startLocationUpdate();
    }
}

Position::~Position()
{
    if(mGeoManager)
    {
        delete mGeoManager;
    }
}

void Position::newPositionReceived(const QGeoCoordinate &coordinate)
{
    if(coordinate.isValid())
    {
        qInfo()<< coordinate;
        if(mGeoManager)
        {
            QGeoCodeReply* reply = mGeoManager->reverseGeocode(coordinate);
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
        else
        {
            qDebug() << "Could not process new Position because geomanager is nullptr";
        }
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
    mPositionResource->requestLocation();
}

}
