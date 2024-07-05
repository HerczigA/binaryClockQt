#pragma once

#include <util.h>
#include <binaryClock.h>
#include <weatherforecast.h>
#include <network.h>
#include <config.h>
#include <position.h>
#include <QNetworkAccessManager>
#include <QMqttClient>
#include <memory>

class MainApp : public QObject
{
    Q_OBJECT
    Q_PROPERTY(BinaryClock* binClock READ binClock CONSTANT)
    Q_PROPERTY(WeatherForecast* weather READ weather CONSTANT)
    Q_PROPERTY(int width READ width CONSTANT)
    Q_PROPERTY(int height READ height CONSTANT)

public:
    void init();
    static MainApp* getInstance(const int& width, const int& height, QObject *parent = nullptr)
    {
        if(s_mainApp == nullptr)
        {
           s_mainApp = new MainApp(width, height, parent);
        }
        return  s_mainApp;
    }

    ~MainApp();
    MainApp(const MainApp& mainapp) = delete;
    BinaryClock* binClock() const;
    WeatherForecast* weather() const;
    const int width() const;
    const int height() const;

public slots:
    void receivedConfig(MainAppComponents::Types type, Properties setting);

private:
    MainApp(const int& w, const int& h, QObject *parent = nullptr)
        : mWidth(w)
        , mHeight(h)
        , QObject(parent)
    {
        mConfig = std::make_unique<Config>();
        mNetwork = std::make_unique<Network>();
        mBinClock = std::make_unique<BinaryClock>();
        mWeatherForecast = std::make_unique<WeatherForecast>();
        mConnections += connect(mWeatherForecast.get(), &WeatherForecast::requestSignal, mNetwork.get(), &Network::newRequest);
        mConnections += connect(mNetwork.get(), &Network::sendData, mWeatherForecast.get(), &WeatherForecast::receivedData);
        mConnections += connect(mConfig.get(), &Config::sendData, mWeatherForecast.get(), &WeatherForecast::receivedConfig);
        mConnections += connect(mConfig.get(), &Config::sendData, this, &MainApp::receivedConfig);
        mConnections += connect(mBinClock.get(), &BinaryClock::updateWeather, mWeatherForecast.get(), &WeatherForecast::requestArrived);
        mConfig->readConfig();
    }
    int mWidth;
    int mHeight;

    static MainApp* s_mainApp;

    std::unique_ptr<Config> mConfig;
    std::unique_ptr<BinaryClock> mBinClock;
    std::unique_ptr<WeatherForecast> mWeatherForecast;
    std::unique_ptr<Network> mNetwork;
    std::unique_ptr<Position> mPos;
    QList<QMetaObject::Connection> mConnections;

};

