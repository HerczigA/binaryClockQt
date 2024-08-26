#pragma once

#include <core/communication/network/network.h>
#include <core/config/config.h>
#include <core/position/PositionResources/PositionResource.h>
//forward declaration in position resource ? 
#include <core/position/PositionResources/PositionPluginResource.h>
#include <core/position/PositionResources/PositionDBusResource.h>
#include <core/position/PositionResources/PositionNetworkResource.h>

#include <QtPositioning/QGeoPositionInfoSource>
#include <QtPositioning/QGeoLocation>
#include <QtPositioning/QGeoAddress>
#include <QtLocation/QGeoCodingManager>
#include <QtLocation/QGeoCodeReply>
#include <QtLocation/QGeoServiceProvider>


#include <QGeoCoordinate>
#include <QDBusInterface>
#include <QVariant>

#include <memory>

namespace position
{

class PositionRequestPackage : public NetworkRequestPackage
{
    public:
        PositionRequestPackage(QObject *parent = nullptr);
        ~PositionRequestPackage();
        void createUrl(const QSharedPointer<QVariant> data) override;
};

class Position : public QObject
{
    Q_OBJECT
public:
    explicit Position(QObject *parent = nullptr);
    enum class ResourceTypes{
            Unknown = -1,
            Plugin,
            Dbus,
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
    void newOnlinePositionReceived(const QByteArray& rawData);
    void requestedLocation();

private slots:
    void newPositionReceived(const QGeoCoordinate &coordinate);

private:
    QGeoCodingManager* mGeoManager;
    std::unique_ptr<QGeoServiceProvider> mServiceProvider;

    QSharedPointer<PositionRequestPackage> mPositionRequestPackage;
    QGeoLocation mGeoLocation;
        
    ResourceTypes mResourceType;
    QSharedPointer<PositionResource> mPositionResource;
};
}

