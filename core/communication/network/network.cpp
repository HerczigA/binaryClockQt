#include "network.h"
#include <QFileInfo>


void NetworkRequestPackage::setRawUrl(const QString &url)
{
    mRawUrl = url;
}

const QString NetworkRequestPackage::getRawUrl() const
{
    return mRawUrl;
}

void NetworkRequestPackage::setOperationType(const QNetworkAccessManager::Operation opType)
{
    mOperationType = opType;
}

const QNetworkAccessManager::Operation NetworkRequestPackage::getOperationType() const
{
    return mOperationType;
}

Network::Network(QObject *parent)
    : QNetworkAccessManager{parent}
    
{
    setIPv6();
}

Network::Network(Credentials &conf, QObject *parent)
    : QNetworkAccessManager{parent}
{

}

Network::~Network()
{

}

const QString Network::parseIPv6()
{
    QHostAddress mLocalAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses())
    {
        if (address.protocol() == QAbstractSocket::IPv6Protocol
            && address != mLocalAddress
            && address.scopeId() == "")
        {
            if(address.toString() != "::1")
            {
                return address.toString();
            }
        }
    }
    return QString();
}

void Network::onRequestPackageReceived(QSharedPointer<NetworkRequestPackage> requestPackage)
{
    if(requestPackage->getRawUrl().isEmpty())
        return;
    
    qDebug() << requestPackage->getRawUrl();

    QNetworkReply* reply = createRequest(requestPackage->getOperationType(),QNetworkRequest(QUrl(requestPackage->getRawUrl())));
    connect(reply, &QNetworkReply::finished, this, &Network::requestReplied);
    connect(this, &QNetworkAccessManager::authenticationRequired, this, &Network::requestReplied);
    connect(reply ,&QNetworkReply::errorOccurred, this, [reply](QNetworkReply::NetworkError code) {
        qDebug() << "error occured. Reason code: " << code << "Reason : " << Config::parseEnumKey<QNetworkReply::NetworkError>(code);
        qDebug() << reply->errorString();
        reply->deleteLater();
    });
}

void Network::requestReplied()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    
    if(reply)
    {
        QByteArray rawData;
        rawData = reply->readAll();
        emit sendRequestResult(rawData);
    }
}

void Network::sharedKeyRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator)
{
    qDebug()<< "shared key required";
}

void Network::sslErrorOccured(QNetworkReply *reply, const QList<QSslError> &errors)
{
    qDebug()<< "ssl error occured";
}

void Network::setAuth(QNetworkReply *reply, QAuthenticator *auth)
{
    (void)*reply;
    auth->setUser(auth->user());
    auth->setPassword(auth->password());
    qDebug()<< "authentication is required";
}

void Network::preSharedKeyCallback(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator)
{
    qDebug()<< "preshared key required";
}

void Network::setIPv6()
{
    mIPv6 = Network::parseIPv6();
}

NetworkRequestPackage::NetworkRequestPackage(QObject *parent)
    :QObject(parent)
{
}

NetworkRequestPackage::~NetworkRequestPackage()
{

}
