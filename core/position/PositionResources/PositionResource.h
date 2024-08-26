#pragma once

#include <QObject>
 
#include <QGeoCoordinate>

namespace position
{

class PositionResource : public QObject
{
    Q_OBJECT

public:
    explicit PositionResource(QObject *parent = nullptr){};
    virtual ~PositionResource(){};
    virtual void requestLocation() = 0;

signals:
    void sendNewCoordinate(const QGeoCoordinate& coordinates);
};

}
