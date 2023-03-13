#pragma once
#include <util.h>
#include <QGeoPositionInfoSource>
#include <QGeoLocation>
#include <QGeoAddress>
#include <QGeoCodingManager>
#include <QGeoCodeReply>
#include <QGeoServiceProvider>

class Position : public QObject
{
    Q_OBJECT
public:
    explicit Position(QObject *parent = nullptr);
    ~Position();

signals:
    void sendCity(QString city);

public slots:
    void newPositionReceived(const QGeoPositionInfo &update);
    void errorReceived(QGeoPositionInfoSource::Error);
    void errorGeoCodeManager();
    void getLocals(QGeoCodeReply *reply);
    void localisationError(QGeoCodeReply::Error error, const QString &errorString = QString());

private:
    QVector<QMetaObject::Connection> mConnections;
    QGeoPositionInfoSource *mGeoPos;
    QGeoLocation mLocation;
    QGeoAddress mAddress;
    QGeoCodingManager * mGeoManager;
    QGeoCodeReply * mGeoCodeReply;
    QGeoServiceProvider mServiceProvider;
};
