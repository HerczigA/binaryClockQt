#pragma once

#include <core/communication/network/network.h>
#include <core/config/config.h>

#include <QtPositioning/QGeoPositionInfoSource>
#include <QtPositioning/QGeoLocation>
#include <QtPositioning/QGeoAddress>
#include <QtLocation/QGeoCodingManager>
#include <QtLocation/QGeoCodeReply>
#include <QtLocation/QGeoServiceProvider>
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

signals:
    void sendCity(QString);
    void requestPackage(QSharedPointer<NetworkRequestPackage> requestPackage);
public slots:
    void newPositionReceived(const QGeoPositionInfo &update);
    void newOnlinePositionReceived(const QByteArray& rawData);
    void errorReceived(QGeoPositionInfoSource::Error);
    void errorGeoCodeManager();
    void getLocals(QGeoCodeReply *reply);
    void localisationError(QGeoCodeReply::Error error, const QString &errorString = QString());
    void requestedLocation();

private:
    QVector<QMetaObject::Connection> mConnections;
    QGeoPositionInfoSource *mGeoPos;
    QGeoLocation mLocation;
    QGeoAddress mAddress;
    QGeoCodingManager * mGeoManager;
    QGeoCodeReply * mGeoCodeReply;
    std::unique_ptr<QGeoServiceProvider> mServiceProvider;
    QSharedPointer<PositionRequestPackage> mPositionRequestPackage;
};
