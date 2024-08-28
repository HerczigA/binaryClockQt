#include "weatherForecastModel.h"

qml::WeatherForecastModel::WeatherForecastModel(QObject *parent)
    : QObject(parent)
{
}

void qml::WeatherForecastModel::requestDataFromUI()
{
    emit requestData();
}

QString qml::WeatherForecastModel::date() const
{
    return mDate.toString("yyyy.MM.dd");
}

QString qml::WeatherForecastModel::location() const
{
    return mLocation;
}

QString qml::WeatherForecastModel::icon() const
{
    return mWeatherIcon;
}

QString qml::WeatherForecastModel::temperature() const
{
    return mTemperature;
}

void qml::WeatherForecastModel::setDate(const QDate &date)
{
    if(mDate != date)
    {
        mDate = date;
        emit dataChanged();
    }
}

void qml::WeatherForecastModel::setLocation(const QString &location)
{
    if(mLocation != location)
    {
        mLocation = location;
        emit dataChanged();
    }
}

void qml::WeatherForecastModel::setIcon(const QString &icon)
{
    if(mWeatherIcon != icon)
    {
        mWeatherIcon = icon;
        emit dataChanged();
    }
}

void qml::WeatherForecastModel::setTemperature(const QString &temperature)
{
    if(mTemperature != temperature)
    {
        mTemperature = temperature;
        emit dataChanged();
    }
}

void qml::WeatherForecastModel::onDateReceived(const QDate &date)
{
    setDate(date);
}

void qml::WeatherForecastModel::onTemperatureReceived(const QString &temperature)
{
    setTemperature(temperature);
}

void qml::WeatherForecastModel::onIconReceived(const QString &icon)
{
    setIcon(icon);
}

void qml::WeatherForecastModel::onLocationReceived(const QString &location)
{
    setLocation(location);
}
