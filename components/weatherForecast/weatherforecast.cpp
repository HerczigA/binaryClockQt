#include "weatherforecast.h"

WeatherForecast::WeatherForecast(QObject *parent)
    : QObject{parent}
{
    mLocation = make_unique<QGeoLocation>();
    mAddress = make_unique<QGeoAddress>(mLocation->address());
    mDate = QDate::currentDate();
    qDebug()<< "mlocation "  << mLocation->isEmpty();
    qDebug()<< "city "  << mAddress->city();


}

WeatherForecast::WeatherForecast(const WeatherForecast &other)
{

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
    return mAddress->city();
//    return QString("Budapest");
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
    if(value != mAddress->city())
    {
        mAddress->setCity(value);
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
//        checking header of doc
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

void WeatherForecast::receivedConfig(MainAppComponents::Types type, SettingProps settings)
{
    if(type == MainAppComponents::Types::WEATHERFORECAST)
    {
        QVariant key = settings.value("apiKey", "");
        mProps.setApiKey(key.toString());
        emit requestSignal(&mProps, MainAppComponents::Types::WEATHERFORECAST);
    }
}
