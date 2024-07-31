#include "weatherforecast.h"

WeatherForecast::WeatherForecast(QObject *parent)
    : QObject{parent}
    , mNetwork(std::make_unique<Network>())
{
}

WeatherForecast::~WeatherForecast()
{
}

void WeatherForecast::requestDataFromUI()
{
    updateLocation();
    sendRequestWeatherData();
}

void WeatherForecast::updateLocation()
{
    emit requestLocation();
}

void WeatherForecast::sendRequestWeatherData()
{
    mNetwork->newRequest();
}

void WeatherForecast::requestArrived()
{
    sendRequestWeatherData()
}

void WeatherForecast::receivedData(MainAppComponents::PropertiesPacket packet)
{
    if (packet.type != MainAppComponents::Types::WeatherForecast)
        return;
    QString newValue;
    for(auto key : packet.props.keys())
    {
        newValue = packet.props.value(key).toString();
        if(key == "temperature")
        {
            emit sendTemperature(newValue);
        }
        else if(key == "icon")
        {
            emit sendIcon(newValue);
        }
    }
}

void WeatherForecast::receivedConfig(MainAppComponents::Types type, Setting settings)
{
    if(type == MainAppComponents::Types::WeatherForecast)
    {
        mProps.mSetting = settings;
        mProps.createUrl();
    }
}

void WeatherForecast::WeatherProps::createUrl()
{
    QString url = mProps["url"].toString();
    QString key = "key=" + mProps["apikey"].toString();
    QString query = "&q=" + getCity() + "&aqi="+ mProps["airQuaility"].toString();
    mUrl = QUrl(url+key+query);
}

const QUrl WeatherForecast::WeatherProps::getUrl()
{
    return mUrl;
}

const QString WeatherForecast::WeatherProps::getCity() const
{
    return mCity; //mProps["city"].toString();
}

void WeatherForecast::WeatherProps::setCity(QString newCity)
{
    mProps.insert("city", QVariant(newCity));
}
