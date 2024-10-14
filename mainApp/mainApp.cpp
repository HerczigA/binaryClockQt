#include "mainApp.h"

#include <ui/Model/Utilities/DateHelper.h>
#include <mainApp/threadModul/threadModul.h>

#include <QQmlEngine>

MainApp *MainApp ::s_mainApp = nullptr; 

MainApp::~MainApp()
{
    mConfig->writeConfig();
    for(auto& connection : mConnections)
        disconnect(connection);
}

qml::BinaryClockModel *MainApp::binClock() const
{
    return mBinaryClockModel.get();
}

qml::WeatherForecastModel *MainApp::weather() const
{
    return mWeatherForecastModel.get();
}

const int MainApp::width() const
{
    return mWidth;
}

const int MainApp::height() const
{
    return mHeight;
}

void MainApp::receivedConfig(const std::shared_ptr<Config::ConfigPacket> packet)
{
    Q_UNUSED(packet);
}


void MainApp::init()
{
    qRegisterMetaType<std::shared_ptr<Config::ConfigPacket>>("std::shared_ptr<Config::ConfigPacket>");
    qRegisterMetaType<QGeoCoordinate>();
    qmlRegisterType<DateHelper>("MainApp.qmlcomponents", 1, 0, "DateHelper");
    mBinaryClock = ThreadModul::createComponentIntoNewThread<BinaryClock>();
    mWeatherForecast = ThreadModul::createComponentIntoNewThread<WeatherForecast>();
    mConfig = ThreadModul::createComponentIntoNewThread<Config>();
    mNetwork = ThreadModul::createComponentIntoNewThread<Network>();
    mPosition = ThreadModul::createComponentIntoNewThread<position::Position>();
    
    mBinaryClockModel = std::make_unique<qml::BinaryClockModel>(this);
    mWeatherForecastModel = std::make_unique<qml::WeatherForecastModel>(this);
}
void MainApp::makeConnections()
{
    mConnections += connect(mNetwork.get(), &Network::sendRequestResult, mWeatherForecast.get(), &WeatherForecast::receivedRequestResult, Qt::QueuedConnection);
    
    mConnections += connect(mWeatherForecast.get(), &WeatherForecast::requestPackage, mNetwork.get(), &Network::onRequestPackageReceived, Qt::QueuedConnection);
    mConnections += connect(mWeatherForecast.get(), &WeatherForecast::sendTemperature, mWeatherForecastModel.get(), &qml::WeatherForecastModel::onTemperatureReceived, Qt::QueuedConnection);
    mConnections += connect(mWeatherForecast.get(), &WeatherForecast::sendIcon, mWeatherForecastModel.get(), &qml::WeatherForecastModel::onIconReceived, Qt::QueuedConnection);
    mConnections += connect(mWeatherForecast.get(), &WeatherForecast::sendLocation, mWeatherForecastModel.get(), &qml::WeatherForecastModel::onLocationReceived, Qt::QueuedConnection);
    mConnections += connect(mWeatherForecast.get(), &WeatherForecast::requestLocation, mPosition.get(), &position::Position::requestedLocation, Qt::QueuedConnection);
    
    mConnections += connect(mPosition.get(), &position::Position::sendLocation, mWeatherForecast.get(), &WeatherForecast::sendLocation, Qt::QueuedConnection);
    mConnections += connect(mConfig.get(), &Config::sendConfigProps, mWeatherForecast.get(), &WeatherForecast::receivedConfig, Qt::QueuedConnection);
    mConnections += connect(mConfig.get(), &Config::sendConfigProps, mPosition.get(), &position::Position::receivedConfig, Qt::QueuedConnection);
    
    mConnections += connect(mWeatherForecastModel.get(), &qml::WeatherForecastModel::requestData, mWeatherForecast.get(), &WeatherForecast::requestArrived, Qt::QueuedConnection);
    mConnections += connect(mBinaryClock.get(), &BinaryClock::timeUnitChanged, mBinaryClockModel.get(), &qml::BinaryClockModel::receivedTimeUnits, Qt::QueuedConnection);
}

