#include "PositionDBusResource.h"

#include <QDBusReply>
#include <QDBusVariant>

namespace position
{

PositionDBusResource::PositionDBusResource(QObject *parent)
{
    mGeoClueManagerInterface = new QDBusInterface("org.freedesktop.GeoClue2",
                                                  "/org/freedesktop/GeoClue2/Manager",
                                                  "org.freedesktop.GeoClue2.Manager",
                                                  QDBusConnection::systemBus());
    if(mGeoClueManagerInterface->isValid())
    {
        QDBusReply<QDBusObjectPath> reply = mGeoClueManagerInterface->call("CreateClient");
        if (reply.isValid()) {
            mClientPath = reply.value().path();
            if(mClientPath.isEmpty())
                return;
            mGeoClueClientInterface = new QDBusInterface("org.freedesktop.GeoClue2",
                                                         mClientPath,
                                                         "org.freedesktop.GeoClue2.Client",
                                                         QDBusConnection::systemBus());
            if(mGeoClueClientInterface->isValid())
            {
                const QVariant desktopId("AviCado");
                bool success = mGeoClueClientInterface->setProperty("DesktopId", desktopId);
                if (success)
                {
                    connect(mGeoClueClientInterface, SIGNAL(LocationUpdated(QDBusObjectPath, QDBusObjectPath)),this, SLOT(handleLocationUpdated(QDBusObjectPath, QDBusObjectPath)));
                }
                else
                {
                    qDebug() << "Failed to set DesktopId";
                }
            }
            else
            {
                qDebug() << "Failed to create GeoClue2 Client interface";
            }
        }
        else
        {
            qDebug() << "Failed to get GeoClue2 client:" << reply.error().message();
        }
    }
    else
    {
        qDebug()<<"Failed to create GeoClue2 Manager interface";
    }
}

PositionDBusResource::~PositionDBusResource()
{
    if (mGeoClueClientInterface) {
        mGeoClueClientInterface->call("Stop");
    }
}

void PositionDBusResource::requestLocation()
{
    /*QDBusReply<void> startReply = mGeoClueClientInterface->call("Start");
    if (!startReply.isValid()) {
        qDebug() << "Failed to call \"Start\" by client:" << startReply.error().message();
    }*/
    QVariant activeStatus = mGeoClueClientInterface->property("Active");
    if(activeStatus.toBool())
    {
        qDebug() << "Client is active";
        QDBusReply<void> startReply = mGeoClueClientInterface->call("Start");
        if (!startReply.isValid()) {
            qDebug() << "Failed to call \"Start\" by client:" << startReply.error().message();
        }
    } else {
        qDebug() << "Failed to get Active property";
    }
}

void PositionDBusResource::handleLocationUpdated(const QDBusObjectPath &oldPath, const QDBusObjectPath &newPath)
{
    qDebug() << "Location updated!";

    QDBusInterface locationInterface("org.freedesktop.GeoClue2",
                                     newPath.path(),
                                     "org.freedesktop.GeoClue2.Location",
                                     QDBusConnection::systemBus());
    if (!locationInterface.isValid()) {
        qDebug() << "Failed to create location interface due to:" << locationInterface.lastError().message();
        return;
    }

    double latitude = locationInterface.property("Latitude").toDouble();
    double longitude = locationInterface.property("Longitude").toDouble();
    QGeoCoordinate coordinate(latitude, longitude);
    emit sendNewCoordinate(coordinate);
    qDebug() << "New location:";
    qDebug() << "Latitude:" << latitude;
    qDebug() << "Longitude:" << longitude;

}

}

