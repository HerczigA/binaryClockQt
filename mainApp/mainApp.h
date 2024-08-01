#pragma once

#include <core/binaryClock/binaryClock.h>
#include <core/weatherForecast/weatherforecast.h>
// #include <core/communication/network/network.h>
#include <core/config/config.h>
// #include <core/position/position.h>
#include <ui/Model/BinaryClockModel/binaryClockModel.h>
#include <ui/Model/WeatherForecastModel/weatherForecastModel.h>


class MainApp : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qml::BinaryClockModel* binClock READ binClock CONSTANT)
    Q_PROPERTY(qml::WeatherForecastModel* weather READ weather CONSTANT)
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
    qml::BinaryClockModel* binClock() const;
    qml::WeatherForecastModel* weather() const;
    const int width() const;
    const int height() const;

public slots:
    void receivedConfig(const std::shared_ptr<Config::ConfigPacket> packet);

private:
    MainApp(const int& w, const int& h, QObject *parent = nullptr)
        : mWidth(w)
        , mHeight(h)
        , QObject(parent)
    {
        init();
        mConnections += connect(mWeatherForecast.get(), &WeatherForecast::requestPackage, mNetwork.get(), &Network::onRequestPackageReceived);
        // mConnections += connect(mNetwork.get(), &Network::sendData, mWeatherForecast.get(), &WeatherForecast::receivedData);
        mConnections += connect(mConfig.get(), &Config::sendConfigProps, mWeatherForecast.get(), &WeatherForecast::receivedConfig);
        mConnections += connect(mConfig.get(), &Config::sendConfigProps, this, &MainApp::receivedConfig);
        mConnections += connect(mBinClock.get(), &BinaryClock::timeUnitChanged, mBinaryClockModel.get(), &qml::BinaryClockModel::receivedTimeUnits, Qt::QueuedConnection);
        // mConnections += connect(mWeatherForecast.get(), &WeatherForecast::sendTemperature, mWeatherForecastModel.get(), &qml::WeatherForecastModel::onTemperatureReceived, Qt::QueuedConnection);
        // mConnections += connect(mWeatherForecast.get(), &WeatherForecast::sendIcon, mWeatherForecastModel.get(), &qml::WeatherForecastModel::onIconReceived, Qt::QueuedConnection);
        // mConnections += connect(mWeatherForecastModel.get(), &qml::WeatherForecastModel::requestData, mWeatherForecast.get(), &WeatherForecast::requestArrived);
        mConfig->readConfig();
    }
    int mWidth;
    int mHeight;

    static MainApp* s_mainApp;

    std::unique_ptr<Config> mConfig;
    std::unique_ptr<BinaryClock> mBinClock;
    std::unique_ptr<WeatherForecast> mWeatherForecast;
    // std::unique_ptr<Network> mNetwork;
    // std::unique_ptr<Position> mPos;
    std::unique_ptr<qml::BinaryClockModel> mBinaryClockModel;
    std::unique_ptr<qml::WeatherForecastModel> mWeatherForecastModel;
    QList<QMetaObject::Connection> mConnections;

};

