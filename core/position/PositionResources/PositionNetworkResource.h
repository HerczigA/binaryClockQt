#pragma once

#include "PositionResource.h"

#include <core/communication/network/network.h>

namespace position
{


class PositionRequestPackage : public NetworkRequestPackage
{
    public:
        PositionRequestPackage(QObject *parent = nullptr);
        ~PositionRequestPackage();
        void createUrl(const QSharedPointer<QVariant> data) override;
};


class PositionNetworkResource : public PositionResource
{
    Q_OBJECT
public:
    PositionNetworkResource(QSharedPointer<ConfigMap> configMap, QObject *parent = nullptr);
    ~PositionNetworkResource();
    virtual void requestLocation() override;
    const PositionRequestPackage* getPositionRequestPackage() const;

signals:
    void sendRequest(QSharedPointer<PositionRequestPackage>);

public slots:
    void receivedResult(QByteArray &rawData);

private:
    QSharedPointer<PositionRequestPackage> mPositionRequestPackage;
    QSharedPointer<Network> mNetwork;
};

}
