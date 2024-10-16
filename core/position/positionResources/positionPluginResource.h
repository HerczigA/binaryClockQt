#pragma once

#include "positionResource.h"

#include <QtPositioning/QGeoPositionInfoSource>
#include <QGeoCoordinate>
#include <QVariant>

namespace position
{

class PositionPluginResource: public PositionResource
{
    Q_OBJECT

public:
    PositionPluginResource(QObject *parent = nullptr);
    ~PositionPluginResource();
    virtual void requestLocation() override;

private slots:
    void newPositionReceived(const QGeoPositionInfo &update);

private:

    QGeoPositionInfoSource *mGeoPos;

};

}

