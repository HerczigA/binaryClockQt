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
    struct PositionProps
    {
        QString mUrl;
        QString mApikey;
        QString mLocation;
        MainAppComponents::Operation  mRequestType;
        PositionProps(QString url, QString apikey)
        : mUrl(url)
        , mApikey("access_key=" + apikey)
        , mRequestType(MainAppComponents::Operation::GET)
        {

        }
        void setUrl(QString url){mUrl = url;}
        void setLocation(QString location){mLocation = location;}
        void setApiKey(QString key){mApikey = "access_key=" +key ;}
        const QString getUrl() const {return mUrl;}
        const QString getLocation () const {return mLocation;}
        const QString getApiKey() const {return mApikey;}
        const MainAppComponents::Operation getRequestType() const {return mRequestType;}
        const QString getRawlUrl() const {return mUrl + mApikey + "&query=" ;}
    };
    explicit Position(QObject *parent = nullptr);
    Position(QString url, QString apikey, QObject *parent = nullptr);
    ~Position();

signals:
    void sendCity(QString city);
    void requestLocation(void* properties, int source);
public slots:
    void newPositionReceived(const QGeoPositionInfo &update);
    void newOnlinePositionReceived(MainAppComponents::Types compType, QByteArray rawData);
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
    unique_ptr<QGeoServiceProvider> mServiceProvider;
    unique_ptr<PositionProps> mProps;
};
