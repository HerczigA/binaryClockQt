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

void WeatherForecast::requestDataFromUI()
{
    // either send request to position or network manager
    updateLocation();
    sendRequestWeatherData();
}

void WeatherForecast::updateLocation()
{
    emit requestLocation();
}

void WeatherForecast::sendRequestWeatherData()
{
    if(mWeatherForecastRequestPackage->getCity().isEmpty())
    {
        emit requestLocation();
    }
    else
    {
        emit requestPackage(mWeatherForecastRequestPackage);
    }
}

void WeatherForecast::requestArrived()
{
    sendRequestWeatherData();
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
        mWeatherForecastRequestPackage = QSharedPointer<WeatherForecastRequestPackage>::create();
        mWeatherForecastRequestPackage->createUrl(QSharedPointer<QVariant>::create(QVariant(packet->mConfigMap)));
        mWeatherForecastRequestPackage->setOperationType(std::move(QNetworkAccessManager::Operation::GetOperation));
        // &QObject::deleteLater
        emit requestPackage(mWeatherForecastRequestPackage); 
    }
}

void WeatherForecast::cityReceived(QSharedPointer<QString> city)
{
    mWeatherForecastRequestPackage->setCity(*city);
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
#if !TESTNETWORK
        QMap configMap = data->toMap();
        QString url = configMap["url"].toString();
        QString key = "key=" + configMap["apikey"].toString();
        QString query = "&q=Budapest&aqi=" + configMap["airQuaility"].toString();
        setUrl(QUrl(url+key+query));
#else
    if(!getCity().isEmpty())
    {
        QMap configMap = data->toMap();
        QString url = configMap["url"].toString();
        QString key = "key=" + configMap["apikey"].toString();
        QString query = "&q=" + getCity() + "&aqi="+ configMap["airQuaility"].toString();
        setUrl(QUrl(url+key+query));
    }

#endif
}

QString WeatherForecastRequestPackage::getCity() const
{
    return mCity;
}

void WeatherForecastRequestPackage::setCity(const QString &city)
{
    mCity = city;
}
