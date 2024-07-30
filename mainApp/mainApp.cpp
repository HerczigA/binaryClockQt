#include "mainApp.h"

MainApp *MainApp ::s_mainApp = nullptr; 

MainApp::~MainApp()
{
    for(auto& connection : mConnections)
        disconnect(connection);
}

qml::BinaryClockModel *MainApp::binClock() const
{
    return mBinaryClockModel.get();
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
            qDebug() << "not online";
        }
        else
        {
            mPos = std::make_unique<Position>(props);
            mConnections += connect(mWeatherForecast.get(), &WeatherForecast::requestLocation, mPos.get(), &Position::requestedLocation);
            mConnections += connect(mPos.get(), &Position::requestLocation, mNetwork.get(), &Network::newRequest);
            mConnections += connect(mNetwork.get(), &Network::sendData, mPos.get(), &Position::newOnlinePositionReceived);
            emit mPos->requestedLocation();
            qDebug() << "online";
        }
        mConnections += connect(mPos.get(), &Position::sendCity, mWeatherForecast.get(), &WeatherForecast::cityUpdated);
    }
    mWeatherForecast->sendRequestWeatherData();
}
