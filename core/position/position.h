#pragma once

#include <QtPositioning/QGeoPositionInfoSource>
#include <QtPositioning/QGeoLocation>
#include <QtPositioning/QGeoAddress>
#include <QtLocation/QGeoCodingManager>
#include <QtLocation/QGeoCodeReply>
#include <QtLocation/QGeoServiceProvider>

class Position : public QObject
{
    Q_OBJECT
public:
    class PositionProps : public MainAppComponents::Props
    {
        public:
            PositionProps(Properties props)
                : Props()
            {
                mRequestType = MainAppComponents::Operation::GET;
                setProps(props);
            }
            ~PositionProps();
            const QString getRawUrl() override;

        };
    explicit Position(QObject *parent = nullptr);
    Position(Properties props, QObject *parent = nullptr);
    ~Position();

signals:
    void sendCity(QString);
    void requestLocation(MainAppComponents::Props* properties, int source);
public slots:
    void newPositionReceived(const QGeoPositionInfo &update);
    void newOnlinePositionReceived(MainAppComponents::PropertiesPacket rawData);
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
    std::unique_ptr<PositionProps> mProps;
};
