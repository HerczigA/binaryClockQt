#include "mainApp.h"

/*MainApp::MainApp(QObject *parent)
    :QObject(parent)
{
    mBinClock = std::make_unique<BinaryClock>();
    mWeatherForecast = std::make_unique<WeatherForecast>();
}

MainApp::MainApp(const int& w, const int& h, QObject *parent)
    : QObject(parent)
    , mWidth(w)
    , mHeight(h)
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
}*/

MainApp::~MainApp()
{
    for(auto& connection : mConnections)
        disconnect(connection);
}

BinaryClock *MainApp::binClock() const
{
    return mBinClock.get();
}

WeatherForecast *MainApp::weather() const
{
    return mWeatherForecast.get();
}

const int MainApp::width() const
{
    return mWidth;
}

const int MainApp::height() const
{
    return mHeight;
}

void MainApp::receivedConfig(MainAppComponents::Types type, Properties props)
{
    if(type == MainAppComponents::Types::Position)
    {
        bool isOnline = props.value("online").toBool();
        if(!isOnline)
        {
            mPos = std::make_unique<Position>();
        }
        else
        {
            mPos = std::make_unique<Position>(props);
            mConnections += connect(mWeatherForecast.get(), &WeatherForecast::requestLocation, mPos.get(), &Position::requestedLocation);
            mConnections += connect(mPos.get(), &Position::requestLocation, mNetwork.get(), &Network::newRequest);
            mConnections += connect(mNetwork.get(), &Network::sendData, mPos.get(), &Position::newOnlinePositionReceived);
            emit mPos->requestedLocation();
        }
        mConnections += connect(mPos.get(), &Position::sendCity, mWeatherForecast.get(), &WeatherForecast::cityUpdated);
    }
    mWeatherForecast->sendRequestWeatherData();
}
