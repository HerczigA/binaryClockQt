#include "network.h"
#include <QFileInfo>


void NetworkRequestPackage::setUrl(const QUrl &url)
{
    mUrl = url;
}

const QUrl NetworkRequestPackage::getUrl() const
{
    return mUrl;
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

void Network::onRequestPackageReceived(QSharedPointer<NetworkRequestPackage> requestPackage)
{
    if(requestPackage->getUrl().isEmpty())
        return;
    
    QNetworkReply* reply = createRequest(requestPackage->getOperationType(),QNetworkRequest(requestPackage->getUrl()));
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
        qInfo()<<"Package arrived and sent " << rawData;
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
    mLocalAddress = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses())
    {

            if (address.protocol() == QAbstractSocket::IPv6Protocol
                && address != mLocalAddress
                && address.scopeId() == "")
        {
            if(address.toString() != "::1")
            {
                mIPv6 = address.toString();
                break;
            }

        }
    }
}

NetworkRequestPackage::NetworkRequestPackage(QObject *parent)
    :QObject(parent)
{
}

NetworkRequestPackage::~NetworkRequestPackage()
{

}
