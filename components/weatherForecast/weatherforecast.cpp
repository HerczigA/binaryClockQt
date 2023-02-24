#include "weatherforecast.h"

WeatherForecast::WeatherForecast(QObject *parent)
    : QObject{parent}
{
    mLocation = make_unique<QGeoLocation>();
    mAddress = make_unique<QGeoAddress>(mLocation->address());
    mDate = QDate::currentDate();

}

WeatherForecast::WeatherForecast(const WeatherForecast &other)
{

}

void WeatherForecast::updateLocation()
{

}

QString WeatherForecast::date() const
{
    return mDate.toString("yyyy.MM.dd");
}

QString WeatherForecast::location() const
{
    return mAddress->city();
//    return QString("Budapest");
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
    if(value != mAddress->city())
    {
        mAddress->setCity(value);
        emit dataChanged();
    }
}

void WeatherForecast::setWeatherDescription(const QString &value)
{

}

void WeatherForecast::setTemperature(const QString &value)
{
    if(value != mTemperature)
    {
        mTemperature=value;
        emit dataChanged();
    }
}
