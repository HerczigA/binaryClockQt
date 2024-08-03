#include "weatherforecast.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>

WeatherForecast::WeatherForecast(QObject *parent)
    : QObject{parent}
{
}

WeatherForecast::~WeatherForecast()
{
}

void WeatherForecast::updateLocation()
{
    if(mWeatherForecastRequestPackage->getLocation().isEmpty())
    {
        emit requestLocation();
    }
}

void WeatherForecast::sendRequestWeatherData()
{
    
    emit requestPackage(mWeatherForecastRequestPackage);
}

void WeatherForecast::requestArrived()
{
    updateLocation();
}

void WeatherForecast::receivedRequestResult(QByteArray& rawData)
{
    if(rawData.contains("weatherapi"))
    {
        QJsonParseError result;
        QJsonDocument document = QJsonDocument::fromJson(rawData, &result);
        if(result.error == QJsonParseError::NoError && !document.isEmpty())
        {
            if(document.isObject())
            {
                QJsonObject object;
                object = document.object();
                if(!object.isEmpty())
                {
                    QJsonValue value = object.value("current");
                    if(!value.isNull())
                    {
                        emit sendTemperature(value["temp_c"].toVariant().toString());
                        QString iconPath = "http:" + value["condition"]["icon"].toString();
                        emit sendIcon(iconPath);
                    }
                }
            }
        }
        else
        {
            qInfo()<< "Error at json parsing object side";
        }
    }    
}

void WeatherForecast::receivedConfig(const std::shared_ptr<Config::ConfigPacket> packet)
{
    if(packet->mConfigType == Config::Types::WeatherForecast)
    { 
        mWeatherForecastRequestPackage.reset();
        mWeatherForecastRequestPackage = QSharedPointer<WeatherForecastRequestPackage>::create(this);
        mWeatherForecastRequestPackage->createUrl(QSharedPointer<QVariant>::create(QVariant(packet->mConfigMap)));
        mWeatherForecastRequestPackage->setOperationType(std::move(QNetworkAccessManager::Operation::GetOperation));
        if(!mWeatherForecastRequestPackage->getLocation().isEmpty())
        {
            emit requestPackage(mWeatherForecastRequestPackage);
        }
    }
}

void WeatherForecast::locationReceived(const QString& location)
{
    mWeatherForecastRequestPackage->setLocation(location);
    mWeatherForecastRequestPackage->updateUrl(location);
    sendRequestWeatherData();
    emit sendLocation(mWeatherForecastRequestPackage->getLocation());
}

WeatherForecastRequestPackage::WeatherForecastRequestPackage(QObject *parent)
    : NetworkRequestPackage(parent)
{
}

WeatherForecastRequestPackage::~WeatherForecastRequestPackage()
{

}

void WeatherForecastRequestPackage::createUrl(const QSharedPointer<QVariant> data)
{
    QString rawUrl;
    if(data)
    {
        ConfigMap configMap = data->toMap();
        QString url = configMap["url"].toString();
        QString key = "key=" + configMap["apikey"].toString();
        QString query = "&q=%1&aqi="+ configMap["airQuaility"].toString();
        rawUrl = url + key+ query;
        setRawUrl(rawUrl);
    }
}

void WeatherForecastRequestPackage::updateUrl(const QString &location)
{
    QString rawUrl = getRawUrl().arg(location);
    setRawUrl(rawUrl);
}

QString WeatherForecastRequestPackage::getLocation() const
{
    return mLocation;
}

void WeatherForecastRequestPackage::setLocation(const QString &location)
{
    if(mLocation != location)
    {
        mLocation = location;
    }
}
