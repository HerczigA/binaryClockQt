#include "mainApp.h"
#include "moc_mainApp.cpp"

MainApp::MainApp(QObject *parent)
    :QObject(parent)
{
    mBinClock = make_unique<BinaryClock>();
    mWeatherForecast = make_unique<WeatherForecast>();
}

MainApp::MainApp(const int& w, const int& h, QObject *parent)
    : QObject(parent)
    , mWidth(w)
    , mHeight(h)
{
    mConfig = make_unique<Config>();
    mPos = make_unique<Position>();
    mNetwork = make_unique<Network>();
    mBinClock = make_unique<BinaryClock>();
    mWeatherForecast = make_unique<WeatherForecast>();
    mConnections += connect(mWeatherForecast.get(), &WeatherForecast::requestSignal, mNetwork.get(), &Network::newRequest);
    mConnections += connect(mNetwork.get(), &Network::sendData, mWeatherForecast.get(), &WeatherForecast::receivedData);
    mConnections += connect(mConfig.get(), &Config::sendData, mWeatherForecast.get(), &WeatherForecast::receivedConfig);
    mConnections += connect(mPos.get(), &Position::sendCity, mWeatherForecast.get(), &WeatherForecast::cityUpdated);
    mConnections += connect(mBinClock.get(), &BinaryClock::updateWeather, mWeatherForecast.get(), &WeatherForecast::requestArrived);

    mConfig->readConfig();
    mWeatherForecast->sendRequestWeatherData();



}

MainApp::~MainApp()
{
    for(auto& connection : mConnections)
        disconnect(connection);
    mNetwork.reset();
    mBinClock.reset();
    mWeatherForecast.reset();
    mConfig.reset();
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
