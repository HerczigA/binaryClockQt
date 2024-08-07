#include "mainApp.h"

#include <ui/Model/Utilities/DateHelper.h>

#include <QQmlEngine>

MainApp *MainApp ::s_mainApp = nullptr; 

void MainApp::init()
{
    qRegisterMetaType<std::shared_ptr<Config::ConfigPacket>>("std::shared_ptr<Config::ConfigPacket>");
    qmlRegisterType<DateHelper>("MainApp.qmlcomponents", 1, 0, "DateHelper");
    mConfig = std::make_unique<Config>(this);
    mNetwork = std::make_unique<Network>();
    mBinClock = std::make_unique<BinaryClock>(this);
    mBinaryClockModel = std::make_unique<qml::BinaryClockModel>(this);
    mWeatherForecast = std::make_unique<WeatherForecast>(this);
    mWeatherForecastModel = std::make_unique<qml::WeatherForecastModel>(this);
}

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
    if(packet->mConfigType == Config::Types::Position)
    {
        bool isOnline = packet->mConfigMap.value("online").toBool();
        if(!isOnline)
        {
            mPos = std::make_unique<Position>();
        }
        else
        {
            mPos = std::make_unique<Position>(packet->mConfigMap);
            mConnections += connect(mWeatherForecast.get(), &WeatherForecast::requestLocation, mPos.get(), &Position::requestedLocation, Qt::QueuedConnection);
            mConnections += connect(mPos.get(), &Position::requestPackage, mNetwork.get(), &Network::onRequestPackageReceived, Qt::QueuedConnection);
            mConnections += connect(mNetwork.get(), &Network::sendRequestResult, mPos.get(), &Position::newOnlinePositionReceived, Qt::QueuedConnection);
        }
        mConnections += connect(mPos.get(), &Position::sendLocation, mWeatherForecast.get(), &WeatherForecast::locationReceived);
        mPos->requestedLocation();
    }
    // mWeatherForecast->sendRequestWeatherData();
}
