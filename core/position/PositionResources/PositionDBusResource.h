#pragma once

#include "PositionResource.h"

#include <QtPositioning/QGeoPositionInfoSource>
#include <QDBusInterface>
#include <QString>

namespace position
{

class PositionDBusResource: public PositionResource
{
    Q_OBJECT

public:
    explicit PositionDBusResource(QObject *parent = nullptr);
    virtual ~PositionDBusResource() override;
    virtual void requestLocation() override;

private slots:
    void handleLocationUpdated(const QDBusObjectPath &oldPath, const QDBusObjectPath &newPath);
private:
    QDBusInterface *mGeoClueManagerInterface;
    QDBusInterface *mGeoClueClientInterface;
    QString mClientPath;

};

}

