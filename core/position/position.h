#pragma once

#include <core/config/config.h>
#include <core/position/positionResources/positionResource.h>
#include <core/position/positionResources/positionPluginResource.h>
#include <core/position/positionResources/positionDBusResource.h>
#include <core/position/positionResources/positionNetworkResource.h>

#include <QtPositioning/QGeoPositionInfoSource>
#include <QtPositioning/QGeoLocation>
#include <QtPositioning/QGeoAddress>
#include <QtLocation/QGeoCodingManager>
#include <QtLocation/QGeoCodeReply>
#include <QtLocation/QGeoServiceProvider>
#include <QGeoCoordinate>
#include <QVariant>

#include <memory>

namespace position
{

class Position : public QObject
{
    Q_OBJECT
public:
    explicit Position(QObject *parent = nullptr);
    enum class ResourceTypes{
            Unknown = -1,
            Plugin,
            DBus,
            GpsDevice,
            Online
    };
    Q_ENUM(ResourceTypes);

    ~Position();
    void startLocationUpdate();

signals:
    void sendLocation(const QString& location);
    void requestPackage(QSharedPointer<NetworkRequestPackage> requestPackage);
    void locationUpdated(const QGeoCoordinate &coordinate);

public slots:
    void receivedConfig(const std::shared_ptr<Config::ConfigPacket> packet);
    void requestedLocation();

private slots:
    void newPositionReceived(const QVariant &coordinate);

private:
    void newOnlinePositionReceived(const QByteArray& rawData);
    void createPositionResource(QSharedPointer<ConfigMap> configMap = nullptr);
    QGeoCodingManager* mGeoManager;
    std::unique_ptr<QGeoServiceProvider> mServiceProvider;
    QGeoLocation mGeoLocation;
    ResourceTypes mResourceType;
    QSharedPointer<PositionResource> mPositionResource;
};

}
