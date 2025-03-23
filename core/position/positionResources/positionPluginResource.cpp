#include "positionPluginResource.h"

#include <core/config/config.h>

namespace position
{
    
constexpr int positionRequestInterval = 15000;

PositionPluginResource::PositionPluginResource(QObject *parent)
    : PositionResource(parent)
{
    QVariantMap params;
    params["desktopId"] = "MainApp";
    mGeoPos = QGeoPositionInfoSource::createSource("geoclue2", params, this);
    if(mGeoPos)
    {
        mGeoPos->setPreferredPositioningMethods(QGeoPositionInfoSource::NonSatellitePositioningMethods);
        connect(mGeoPos, &QGeoPositionInfoSource::positionUpdated, this, &PositionPluginResource::newPositionReceived, Qt::QueuedConnection);
        connect(mGeoPos, &QGeoPositionInfoSource::errorOccurred, this, [](QGeoPositionInfoSource::Error error)
                {
                    qDebug() << "Error occured when plugin tried to request update. Error reason: " << Config::parseEnumKeyToString<QGeoPositionInfoSource::Error>(error);
                }, Qt::QueuedConnection);
    }
    else
        qInfo()<< "Cannot connect to GeoClue2 plugin";
}

PositionPluginResource::~PositionPluginResource()
{
}

void PositionPluginResource::requestLocation()
{
    if(mGeoPos)
    { 
        mGeoPos->requestUpdate(positionRequestInterval);
    }
}

void PositionPluginResource::newPositionReceived(const QGeoPositionInfo &newPos)
{
    if(newPos.isValid())
    {
        qInfo()<< newPos.coordinate();
        emit sendNewResult(QVariant::fromValue(newPos.coordinate()));
    }
}

}

