#include "weatherforecast.h"

WeatherForecast::WeatherForecast(QObject *parent)
    : QObject{parent}
{
    mLocation = make_unique<QGeoLocation>();
    mDate = QDate::currentDate();
}

WeatherForecast::WeatherForecast(const WeatherForecast &other)
{

}

void WeatherForecast::updateLocation()
{

}

QString WeatherForecast::dayOfWeek() const
{
    return mDayOfTheWeek;
}

QString WeatherForecast::location() const
{
    QGeoAddress address = mLocation->address();
    return address.city();
}

//QString WeatherForecast::weatherIcon() const
//{

//}

QString WeatherForecast::weatherDescription() const
{
    return mWeatherDescription;
}

QString WeatherForecast::temperature() const
{
    return mTemperature;
}

void WeatherForecast::setDayOfWeek(const QString &value)
{

}

void WeatherForecast::setLocation(const QString &value)
{

}

void WeatherForecast::setWeatherDescription(const QString &value)
{

}

void WeatherForecast::setTemperature(const QString &value)
{

}
