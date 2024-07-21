#include "weatherForecastModel.h"

void WeatherForecastModel::requestDataFromUI()
{
    emit requestDate();
}

QString WeatherForecastModel::date() const
{
    return mDate.toString("yyyy.MM.dd");
}

QString WeatherForecastModel::location() const
{
    return mLocation;
}

QString WeatherForecastModel::icon() const
{
    return mWeatherIcon;
}

QString WeatherForecastModel::temperature() const
{
    return mTemperature;
}

void WeatherForecastModel::setDate(const QDate &date)
{
    if(mDate != date)
    {
        mDate = date;
        emit dataChanged();
    }
}

void WeatherForecastModel::setLocation(const QString &location)
{
    if(mLocation != location)
    {
        mLocation = location;
        emit dataChanged();
    }
}

void WeatherForecastModel::setIcon(const QString &icon)
{
    if(mWeatherIcon != icon)
    {
        mWeatherIcon = icon;
        emit dataChanged();
    }
}

void WeatherForecastModel::setTemperature(const QString &temperature)
{
    if(mTemperature != temperature)
    {
        mTemperature = temperature;
        emit dataChanged();
    }
}

void WeatherForecastModel::onDateReceived(const QDate &date)
{
    setDate(date);
}

void WeatherForecastModel::onTemperatureReceived(const QString &temperature)
{
    setTemperature(temperature);
}

void WeatherForecastModel::onLocationReceived(const QString &location)
{
    setLocation(location);
}
