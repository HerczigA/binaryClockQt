#pragma once

#include <core/config/config.h>
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

class NetworkRequestPackage : public QObject
{
    Q_OBJECT
    public:
        explicit NetworkRequestPackage(QObject* parent);
        virtual ~NetworkRequestPackage();
        virtual void createUrl(const QSharedPointer<QVariant> data) = 0;
        void setRawUrl(const QString& rawUrl);
        void setOperationType(const QNetworkAccessManager::Operation opType);
        const QString getRawUrl() const;
        const QNetworkAccessManager::Operation getOperationType() const;
    private:
        QString mRawUrl;
        QNetworkAccessManager::Operation mOperationType = QNetworkAccessManager::Operation::UnknownOperation;
};

class Network : public QNetworkAccessManager
{
    Q_OBJECT

    public:
        explicit Network(QObject *parent = nullptr);
        Network(struct Credentials& conf, QObject *parent = nullptr);
        ~Network();
        static const QString parseIPv6();

    signals:
        void sendRequestResult(QByteArray &rawData);

    public slots:
        void onRequestPackageReceived(QSharedPointer<NetworkRequestPackage> requestPackage);
        void requestReplied();

        void sharedKeyRequired(QNetworkReply*, QSslPreSharedKeyAuthenticator*);
        void sslErrorOccured(QNetworkReply*, const QList<QSslError>&);
        void setAuth(QNetworkReply*, QAuthenticator*);
        void preSharedKeyCallback(QNetworkReply*, QSslPreSharedKeyAuthenticator*);

    private slots:
        //for tls-ssl
        // void errorOccured(QNetworkReply::NetworkError);
    //    void encryptedSlot(QNetworkReply*);

    private:
        void setIPv6();

        QNetworkRequest mRequest;
        Credentials mCredentials;
        QVector<QMetaObject::Connection> mConnections;
        QSslConfiguration mSslConf;
        QHostAddress mLocalAddress;
        QString mIPv6;
        // JsonHandler mJson;

};
