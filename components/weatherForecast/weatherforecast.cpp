#include "weatherforecast.h"
#include "moc_weatherforecast.cpp"

WeatherForecast::WeatherForecast(QObject *parent)
    : QObject{parent}
{

    mDate = QDate::currentDate();

}

WeatherForecast::WeatherForecast(const WeatherForecast &other)
{

}

WeatherForecast::~WeatherForecast()
{
    for(auto con : mConnections)
        disconnect(con);
}

void WeatherForecast::updateLocation()
{

}

void WeatherForecast::sendRequestWeatherData()
{
    emit requestSignal(&mProps, MainAppComponents::Types::WEATHERFORECAST);
}

QString WeatherForecast::date() const
{
    return mDate.toString("yyyy.MM.dd");
}

QString WeatherForecast::location() const
{
    return mCityLocation;
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
    if(mCityLocation != value)
    {
        qInfo()<< "mCityLocation before" << mCityLocation;
        mCityLocation = value;
        qInfo()<< "mCityLocation after"<< mCityLocation;
        emit dataChanged();
    }
}

void WeatherForecast::setIcon(const QString &value)
{
    if(value != mWeatherIcon)
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
    emit requestSignal(&mProps, MainAppComponents::Types::WEATHERFORECAST);
}

void WeatherForecast::receivedData(MainAppComponents::Types type, QByteArray rawData)
{
    if (type != MainAppComponents::Types::WEATHERFORECAST)
        return;


    QJsonParseError result;
    QJsonValue value;
    QJsonObject obj;
    QJsonDocument document = QJsonDocument::fromJson(rawData, &result);
    if(result.error == QJsonParseError::NoError && !document.isEmpty())
    {

        if(document.isObject())
            obj = document.object();
        else{
            qDebug()<< "error at json parsing object side";
            return;
        }
        value = obj.value("current");
        if(!value.isNull())
        {
            QString newValue= value["temp_c"].toVariant().toString();
            newValue += " °C";
            setTemperature(newValue);
            newValue = value["condition"]["icon"].toVariant().toString();
            if(!newValue.isEmpty() && newValue.contains("//"))
            {
                newValue = newValue.right(newValue.size()-2);
                setIcon(newValue);
            }


        }
    }
    else
        sendRequestWeatherData();

}

void WeatherForecast::receivedConfig(MainAppComponents::Types type, SettingMap  settings)
{
    if(type == MainAppComponents::Types::WEATHERFORECAST)
    {
        QVariant key = settings.value("apiKey", "");
        mProps.setApiKey(key.toString());
        emit requestSignal(&mProps, MainAppComponents::Types::WEATHERFORECAST);
    }
}

void WeatherForecast::cityUpdated(QString city)
{
    setLocation(city);
}
