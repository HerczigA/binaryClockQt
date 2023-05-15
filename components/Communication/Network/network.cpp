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
//    mConnections.push_back(connect(mReply ,&QNetworkReply::errorOccurred, this, &Network::replyErrorReceived));
}

Network::Network(Credentials &conf, QObject *parent)
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

void Network::newRequest(MainAppComponents::Props* properties, int source)
{
    mRequestType = UnknownOperation;
    QString rawUrl = properties->getRawUrl();
    switch (source) {
        case MainAppComponents::Types::WeatherForecast:
        {
            WeatherForecast::WeatherProps * prop = reinterpret_cast<WeatherForecast::WeatherProps*>(properties);
            if(prop)
            {
                if(prop->getCity() == "")
                    return;
            }
            break;
        }
        case MainAppComponents::Types::Position:
        {
            rawUrl += mIPv6;
            break;
        }
        default:
            break;
        }

    QUrl url = QUrl(rawUrl);
    mRequestType = static_cast<QNetworkAccessManager::Operation>(properties->getRequestType());
    mRequest = QNetworkRequest(url);

    if(mRequestType)
        createRequest( mRequestType, mRequest);
}

void Network::requestReplied(QNetworkReply* reply)
{
    QByteArray rawData;
    MainAppComponents::Types type;
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

    type = mReply->url().host().contains("position")
        ? MainAppComponents::Types::Position
        : MainAppComponents::Types::WeatherForecast;

    emit sendData(type, rawData);

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
