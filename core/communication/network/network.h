#pragma once

#include <core/communication/network/extensions/jsonhandler.h>
#include <core/config/config.h>
#include <core/weatherForecast/weatherforecast.h>

#include <QSharedPointer>
#include <QVariant>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QAuthenticator>
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QHostAddress>



class Credentials : public QAuthenticator
{
    public:
    const QString apiKey() const { return  mApiKey; }
    void setApiKey(QString& newApiKey){ mApiKey = newApiKey; }

    private:
        QString mApiKey;
};

class NetworkRequestPackage : public QNetworkAccessManager
{
    Q_OBJECT
    public:
        // NetworkRequestPackage(Config::Types sourceType);
        virtual ~NetworkRequestPackage();
        virtual void createUrl(const QSharedPointer<QVariant> data) = 0;
        void setUrl(const QUrl& url);
        void setOperationType(const QNetworkAccessManager::Operation opType);
        const QUrl getUrl() const;
    private:
        QUrl mUrl;
        // Config::Types mSourceType;
        QNetworkAccessManager::Operation mOperationType = QNetworkAccessManager::Operation::UnknownOperation;
};

class Network : public QObject
{
    Q_OBJECT

    public:
        explicit Network(QObject *parent = nullptr);
        Network(struct Credentials& conf, QObject *parent = nullptr);
        ~Network();

    signals:
        void sendData(Config::ConfigPacket packet);

    public slots:
        void onRequestPackageReceived(QSharedPointer<NetworkRequestPackage> requestPackage);
        void requestReplied(QNetworkReply*);

        void sharedKeyRequired(QNetworkReply*, QSslPreSharedKeyAuthenticator*);
        void sslErrorOccured(QNetworkReply*, const QList<QSslError>&);
        void setAuth(QNetworkReply*, QAuthenticator*);
        void preSharedKeyCallback(QNetworkReply*, QSslPreSharedKeyAuthenticator*);


    private slots:
        //for tls-ssl
        // void errorOccured(QNetworkReply::NetworkError);
    //    void encryptedSlot(QNetworkReply*);

    private:
        void getRequest(QNetworkAccessManager::Operation op, const QUrl &url);
        void setIPv6();

        QNetworkRequest mRequest;
        QNetworkReply *mReply;
        Credentials mCredentials;
        QVector<QMetaObject::Connection> mConnections;
        QSslConfiguration mSslConf;
        QHostAddress mLocalAddress;
        QString mIPv6;
        JsonHandler mJson;

};
