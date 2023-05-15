#pragma once
#include <util.h>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMqttClient>
#include <QAuthenticator>
//#include <QHostInfo>
#include <QNetworkInterface>
#include <QHostAddress>
#include <weatherforecast.h>
#include <position.h>
class Credentials : public QAuthenticator
{
    public:
    const QString apiKey() const { return  mApiKey; }
    void setApiKey(QString& newApiKey){ mApiKey = newApiKey; }

    private:
        QString mApiKey;
};

class Network : public QNetworkAccessManager
{
    Q_OBJECT

public:
    explicit Network(QObject *parent = nullptr);
    Network(struct Credentials& conf, QObject *parent = nullptr);
    virtual ~Network();

signals:
    void sendData(MainAppComponents::Types compType, QByteArray rawData);

public slots:
    void newRequest(MainAppComponents::Props * properties, int source);
    void requestReplied(QNetworkReply*);


    void sharedKeyRequired(QNetworkReply*, QSslPreSharedKeyAuthenticator*);
    void sslErrorOccured(QNetworkReply*, const QList<QSslError>&);
    void setAuth(QNetworkReply*, QAuthenticator*);
    void preSharedKeyCallback(QNetworkReply*, QSslPreSharedKeyAuthenticator*);


private slots:
    //for tls-ssl
//    void encryptedSlot(QNetworkReply*);

private:
    void createRequest(Operation op, const QNetworkRequest & req);
    void setIPv6();

    QNetworkRequest mRequest;
    QNetworkReply *mReply;
    Credentials mCredentials;
    QNetworkAccessManager::Operation mRequestType;
    QAuthenticator mAuth;
    QVector<QMetaObject::Connection> mConnections;
    QSslConfiguration mSslConf;
    QHostAddress mLocalAddress;
    QString mIPv6;
};
