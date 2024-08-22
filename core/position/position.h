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
    Position(const ConfigMap& configMap);
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
    void errorReceived(QGeoPositionInfoSource::Error);
    void errorGeoCodeManager();
    void getLocals(QGeoCodeReply *reply);
    void localisationError(QGeoCodeReply::Error error, const QString &errorString = QString());
    void requestedLocation();



    void handleLocationUpdated(const QDBusObjectPath &oldPath, const QDBusObjectPath &newPath);
    
    void handleLocationUpdated(QString, QString);

private:
    void createDBusClient();
    void createPluginClient();
    void createNetworkRequest();
    
    
    QVector<QMetaObject::Connection> mConnections;
    QGeoPositionInfoSource *mGeoPos;

    QGeoCodingManager * mGeoManager;

    std::unique_ptr<QGeoServiceProvider> mServiceProvider;

    QSharedPointer<PositionRequestPackage> mPositionRequestPackage;

    QDBusInterface *m_geoClueManagerInterface;
    QDBusInterface *mGeoClueClientInterface;
    QString m_clientPath;

    QString mRawUrl;
    QString mApiKey;
};
