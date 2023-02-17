#pragma once
#include <QObject>
#include <QQuickItem>

class WeatherForecast : public QObject
{
    Q_OBJECT
public:
    explicit WeatherForecast(QObject *parent = nullptr);

signals:

};


