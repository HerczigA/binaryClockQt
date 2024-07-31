#include "mainApp.h"

MainApp *MainApp ::s_mainApp = nullptr; 

void MainApp::init()
{
    qRegisterMetaType<std::shared_ptr<Config::ConfigPacket>>("std::shared_ptr<Config::ConfigPacket>");
}

MainApp::~MainApp()
{
    for(auto& connection : mConnections)
        disconnect(connection);
}

qml::BinaryClockModel *MainApp::binClock() const
{
    return mBinaryClockModel.get();
}

// WeatherForecast *MainApp::weather() const
// {
//     return mWeatherForecast.get();
// }

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
            // mPos = std::make_unique<Position>();
            qDebug() << "GPS";
        }
        else
        {
            // mPos = std::make_unique<Position>(props);
            // mConnections += connect(mWeatherForecast.get(), &WeatherForecast::requestLocation, mPos.get(), &Position::requestedLocation);
            // mConnections += connect(mPos.get(), &Position::requestLocation, mNetwork.get(), &Network::newRequest);
            // mConnections += connect(mNetwork.get(), &Network::sendData, mPos.get(), &Position::newOnlinePositionReceived);
            // emit mPos->requestedLocation();
            qDebug() << "online";
        }
        // mConnections += connect(mPos.get(), &Position::sendCity, mWeatherForecast.get(), &WeatherForecast::cityUpdated);
    }
    // mWeatherForecast->sendRequestWeatherData();
}
