#pragma once
#include <util.h>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMqttClient>
#include <QAuthenticator>

#include <weatherforecast.h>

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
    enum SourceTypes
    {
        Unknow,
        Weather
    };

public:
    explicit Network(QObject *parent = nullptr);
    Network(struct AuthConf& conf, QObject *parent = nullptr);
    virtual ~Network();

signals:
    void sendData(MainAppComponents::Types compType, QByteArray rawData);

public slots:
    void newRequest(void* properties, int source);
    void requestReplied(QNetworkReply*);
    void sharedKeyRequired(QNetworkReply*, QSslPreSharedKeyAuthenticator*);
    void sslErrorOccured(QNetworkReply*, const QList<QSslError>&);
    void setAuth(QNetworkReply*, QAuthenticator*);
    void preSharedKeyCallback(QNetworkReply*, QSslPreSharedKeyAuthenticator*);


private slots:
    void replyErrorReceived(QNetworkReply::NetworkError code);
    //for tls-ssl
//    void encryptedSlot(QNetworkReply*);

private:
    void createRequest(Operation op, const QNetworkRequest & req);

    QNetworkRequest mRequest;
    QNetworkReply *mReply;
    Credentials mCredentials;
    QNetworkAccessManager::Operation mRequestType;
    QAuthenticator mAuth;
    QVector<QMetaObject::Connection> mConnections;
    QSslConfiguration* mSslConf;


};
