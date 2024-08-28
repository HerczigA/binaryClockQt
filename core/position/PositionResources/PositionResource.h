#pragma once

#include <QObject>
 
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
    void sendNewResult(const QVariant& result);
};

}
