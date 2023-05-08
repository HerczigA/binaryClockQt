#include "network.h"
#include "moc_network.cpp"

Network::Network(QObject *parent)
    : QNetworkAccessManager{parent}
    , mRequestType(UnknownOperation)
{
    setIPv6();
    mConnections.push_back(connect(this,&QNetworkAccessManager::finished, this, &Network::requestReplied));
    mConnections.push_back(connect(this,&QNetworkAccessManager::authenticationRequired, this, &Network::setAuth));
    mConnections.push_back(connect(this,&QNetworkAccessManager::sslErrors, this, &Network::sslErrorOccured));
    mConnections.push_back(connect(this,&QNetworkAccessManager::preSharedKeyAuthenticationRequired, this, &Network::preSharedKeyCallback));
    mConnections.push_back(connect(mReply ,&QNetworkReply::errorOccurred, this, &Network::replyErrorReceived));
    connectToHostEncrypted(weatherApiUrls);

}

Network::Network(AuthConf &conf, QObject *parent)
    : QNetworkAccessManager{parent}
{

}
Network::~Network()
{
    if(mReply)
        delete mReply;


    for(auto& connection : mConnections)
        disconnect(connection);
}

void Network::newRequest(void* properties, int source)
{
     switch (source) {
        case MainAppComponents::Types::WeatherForecast:
        {
            WeatherForecast::WeatherProps* prop = reinterpret_cast<WeatherForecast::WeatherProps*>(properties);
            if(prop)
            {
                if(prop->getCity() == "")
                    return;
                QString rawUrl = prop->getRawUrl();
                QUrl url = QUrl(rawUrl);
                mRequestType = static_cast<QNetworkAccessManager::Operation>(prop->getRequestType());
                mRequest = QNetworkRequest(url);
//                "https://api.weatherapi.com/v1/current.json?key=d9af10fd8f83457ea2184652232302&q=&aqi=no"
            }
            else
            {
                mRequestType = UnknownOperation;
            }

            break;
        }
        case MainAppComponents::Types::Position:
        {
            Position::PositionProps* prop = reinterpret_cast<Position::PositionProps*>(properties);
            if(prop)
            {
                QString rawUrl = prop->getRawlUrl() + mIPv6;
                QUrl url = QUrl(rawUrl);
//                "https://positionstack.com/v1/reverse?a8fc06c3426b2a8c0a039656d7162403&query=2a02:ab88:5984:9100:d874:4303:c231:a3f8"
                mRequestType = static_cast<QNetworkAccessManager::Operation>(prop->getRequestType());
                mRequest = QNetworkRequest(url);
            }
            else
            {
                mRequestType = UnknownOperation;
            }
        }
        default:
            break;
    }

    if(mRequestType)
        createRequest( mRequestType, mRequest);


}

void Network::requestReplied(QNetworkReply* reply)
{
    QByteArray rawData;;
    if(mReply != reply)
        mReply = reply;

    if(mReply->error() == QNetworkReply::NoError)
    {
        rawData = mReply->readAll();
    }
    else
    {
        qDebug()<< "Logged error occurred : "  << mReply->errorString();
    }
    emit sendData(MainAppComponents::Types::WeatherForecast, rawData);

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
    if(mRequest.url() != QUrl("") && mRequestType != UnknownOperation)
        createRequest(mRequestType, mRequest);

}

void Network::preSharedKeyCallback(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator)
{
    qDebug()<< "preshared key required";
}

void Network::replyErrorReceived(QNetworkReply::NetworkError code)
{
    qDebug()<<"Received error code from network reply "<< code;
}

void Network::createRequest(Operation op, const QNetworkRequest &req)
{

    switch (op) {
        case GetOperation:
        {
            mReply = get(req);
            break;
        }
        default:
            break;
        }
}

void Network::setIPv6()
{
    mLocalAddress = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv6Protocol
                && address != mLocalAddress
                && address.scopeId() == "")
        {
            if(address.toString() != "::1")
                mIPv6 = address.toString();
        }
    }
}
