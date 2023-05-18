#include "weatherforecast.h"
#include "moc_weatherforecast.cpp"

WeatherForecast::WeatherForecast(QObject *parent)
    : QObject{parent}
{

    mDate = QDate::currentDate();
    updateLocation();
}

WeatherForecast::WeatherForecast(const WeatherForecast &other)
{

}

WeatherForecast::~WeatherForecast()
{
    for(auto &con : mConnections)
        disconnect(con);
}

void WeatherForecast::updateLocation()
{
    emit requestLocation();
}

void WeatherForecast::sendRequestWeatherData()
{
    emit requestSignal(&mProps, MainAppComponents::Types::WeatherForecast);
}

QString WeatherForecast::date() const
{
    return mDate.toString("yyyy.MM.dd");
}

QString WeatherForecast::location() const
{
    return mProps.getCity();
}

//QString WeatherForecast::weatherIcon() const
//{

//}

QString WeatherForecast::icon() const
{
    return mWeatherIcon;
}

QString WeatherForecast::temperature() const
{
    return mTemperature;
}

void WeatherForecast::setDate(const QString &value)
{
    if(value != mDayOfTheWeek)
    {
        mDayOfTheWeek=value;
        emit dataChanged();
    }
}

void WeatherForecast::setLocation(const QString &value)
{
    if(mProps.getCity() != value)
    {
        mProps.setCity(value);
        emit requestSignal(&mProps, MainAppComponents::Types::WeatherForecast);
        emit dataChanged();
    }
}

void WeatherForecast::setIcon(const QString &value)
{
    if(mWeatherIcon != value)
    {
        mWeatherIcon = value;
        emit dataChanged();
    }
}

void WeatherForecast::setTemperature(const QString &value)
{
    if(value != mTemperature)
    {
        mTemperature=value;
        emit dataChanged();
    }
}

void WeatherForecast::requestArrived()
{
    emit requestSignal(&mProps, MainAppComponents::Types::WeatherForecast);
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
            setTemperature(newValue);
        }
        else if(key == "icon")
        {
            setIcon(newValue);
        }
    }
//    sendRequestWeatherData();

}

void WeatherForecast::receivedConfig(MainAppComponents::Types type, Properties settings)
{
    if(type == MainAppComponents::Types::WeatherForecast)
    {
        mProps.setProps(settings);
        emit requestSignal(&mProps, MainAppComponents::Types::WeatherForecast);
    }
}

void WeatherForecast::cityUpdated(QString var)
{
    setLocation(var);
}

const QString WeatherForecast::WeatherProps::getRawUrl()
{
    QString url = mProps["url"].toString();
    QString key = "key=" + mProps["apikey"].toString();
    QString query = "&q=" + getCity() + "&aqi="+ mProps["airQuaility"].toString();
    return url + key + query;
}

const QString WeatherForecast::WeatherProps::getCity() const
{
    return mProps["city"].toString();
}

void WeatherForecast::WeatherProps::setCity(QString newCity)
{
    mProps.insert("city", QVariant(newCity));
}
