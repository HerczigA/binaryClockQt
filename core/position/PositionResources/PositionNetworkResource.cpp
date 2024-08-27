#include "PositionNetworkResource.h"


namespace position
{

PositionRequestPackage::PositionRequestPackage(QObject *parent)
    :NetworkRequestPackage(parent)
{
}

PositionRequestPackage::~PositionRequestPackage()
{
}

void PositionRequestPackage::createUrl(const QSharedPointer<QVariant> data)
{
    QString rawUrl;
    if(data->canConvert<ConfigMap>())
    {
        ConfigMap configMap = data->toMap();
        QString url = configMap["url"].toString();
        QString key = "access_key=" +configMap["apikey"].toString();
        QString query = "&query="+ Network::parseIPv6();
        rawUrl = url+key+query;
        setRawUrl(rawUrl);
    }
}


PositionNetworkResource::PositionNetworkResource(QSharedPointer<ConfigMap> configMap, QObject *parent)
    : PositionResource(parent)
{
    if(configMap)
    {
        mNetwork = QSharedPointer<Network>::create(this);
        mPositionRequestPackage = QSharedPointer<PositionRequestPackage>::create(this);
        mPositionRequestPackage->createUrl(QSharedPointer<QVariant>::create(QVariant(*configMap)));
        mPositionRequestPackage->setOperationType(std::move(QNetworkAccessManager::Operation::GetOperation));
        connect(this, &PositionNetworkResource::sendRequest, mNetwork.get(), &Network::onRequestPackageReceived, Qt::QueuedConnection);
        connect(mNetwork.get(), &Network::sendRequestResult, this, &PositionNetworkResource::receivedResult, Qt::QueuedConnection);
    }
}

PositionNetworkResource::~PositionNetworkResource()
{

}

void PositionNetworkResource::requestLocation()
{
    emit sendRequest(mPositionRequestPackage);
}

void PositionNetworkResource::receivedResult(QByteArray &rawData)
{
    emit sendNewResult(QVariant::fromValue(rawData));
}

const PositionRequestPackage* PositionNetworkResource::getPositionRequestPackage() const
{
    return mPositionRequestPackage.get();
}
}
