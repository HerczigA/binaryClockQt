#pragma once

#include <core/communication/network/network.h>
#include <core/config/config.h>

#include <QtPositioning/QGeoPositionInfoSource>
#include <QtPositioning/QGeoLocation>
#include <QtPositioning/QGeoAddress>
#include <QtLocation/QGeoCodingManager>
#include <QtLocation/QGeoCodeReply>
#include <QtLocation/QGeoServiceProvider>


#include <QGeoCoordinate>
#include <QDBusInterface>

#include <QVariant>

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
    enum class PositionResources{
            Unknown = -1,
            Plugin,
            Dbus,
            GpsDevice,
            Online
    };
    Q_ENUM(PositionResources);

    ~Position();
    void startLocationUpdate();

signals:
    void sendLocation(const QString& location);
    void requestPackage(QSharedPointer<NetworkRequestPackage> requestPackage);

    void locationUpdated(const QGeoCoordinate &coordinate);

public slots:
    void receivedConfig(const std::shared_ptr<Config::ConfigPacket> packet);
    void newPositionReceived(const QGeoPositionInfo &update);
    void newOnlinePositionReceived(const QByteArray& rawData);
    void requestedLocation();

private slots:
    void handleLocationUpdated(const QDBusObjectPath &oldPath, const QDBusObjectPath &newPath);

private:
    void createDBusClient();
    void createPluginClient();
    void createNetworkRequest();
    
    QGeoPositionInfoSource *mGeoPos;

    QGeoCodingManager* mGeoManager;
    std::unique_ptr<QGeoServiceProvider> mServiceProvider;

    QSharedPointer<PositionRequestPackage> mPositionRequestPackage;
    QGeoLocation mGeoLocation;
    QDBusInterface *mGeoClueManagerInterface;
    QDBusInterface *mGeoClueClientInterface;
    QString mClientPath;
    PositionResources mResourceType;
        
};
