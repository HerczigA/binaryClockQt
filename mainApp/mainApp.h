#pragma once

#include <util.h>
#include <binaryClock.h>
#include <weatherforecast.h>
#include <network.h>
#include <config.h>
#include <position.h>
#include <QNetworkAccessManager>
#include <QMqttClient>

class MainApp : public QObject
{
    Q_OBJECT
    Q_PROPERTY(BinaryClock* binClock READ binClock CONSTANT)
    Q_PROPERTY(WeatherForecast* weather READ weather CONSTANT)
    Q_PROPERTY(int width READ width CONSTANT)
    Q_PROPERTY(int height READ height CONSTANT)

public:
    explicit MainApp(QObject *parent = nullptr);
    MainApp(const int& w, const int& h, QObject *parent = nullptr);
    ~MainApp();
    BinaryClock* binClock() const;
    WeatherForecast* weather() const;
    const int width() const;
    const int height() const;

public slots:
    void receivedConfig(MainAppComponents::Types type, Properties setting);

private:
    int mWidth;
    int mHeight;
    unique_ptr<Config> mConfig;
    unique_ptr<BinaryClock> mBinClock;
    unique_ptr<WeatherForecast> mWeatherForecast;
    unique_ptr<Network> mNetwork;
    unique_ptr<Position> mPos;
    QList<QMetaObject::Connection> mConnections;

};

