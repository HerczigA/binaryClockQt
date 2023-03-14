#include "network.h"
#include "moc_network.cpp"

Network::Network(QObject *parent)
    : QNetworkAccessManager{parent}
    , mRequestType(UnknownOperation)
{

    mConnections.push_back(connect(this,&QNetworkAccessManager::finished, this, &Network::requestReplied));
    mConnections.push_back(connect(this,&QNetworkAccessManager::authenticationRequired, this, &Network::setAuth));
    mConnections.push_back(connect(this,&QNetworkAccessManager::sslErrors, this, &Network::sslErrorOccured));
    mConnections.push_back(connect(this,&QNetworkAccessManager::preSharedKeyAuthenticationRequired, this, &Network::preSharedKeyCallback));
//    mConnections.push_back(connect(mReply ,&QNetworkReply::errorOccurred, this, &Network::replyErrorReceived));

//    connectToHostEncrypted(weatherApiUrls);
//    connectToHostEncrypted(weatherApiUrls);
//    connectToHostEncrypted("https://www.jsontest.com");
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
        case SourceTypes::Weather:
        {
            WeatherProps* prop = reinterpret_cast<WeatherProps*>(properties);
            if(prop)
            {
                QString rawUrl = prop->url + prop->apiKey + prop->city + prop->airQuality;
                QUrl url = QUrl(rawUrl);
                mRequestType = static_cast<QNetworkAccessManager::Operation>(prop->requestType);
                mRequest = QNetworkRequest(url);
            }
            else
                mRequestType = UnknownOperation;
            break;
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
    emit sendData(MainAppComponents::Types::WEATHERFORECAST, rawData);

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
