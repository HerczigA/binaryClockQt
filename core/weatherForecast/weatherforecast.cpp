#include "weatherforecast.h"

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

void WeatherForecast::receivedData(QSharedPointer<QVariant> data)
{
    if(data->canConvert<QVariantMap>())
    {
        QString newValue;
        QMap<QString, QVariant> package = data->toMap();
        for(auto key : package.keys())
        {
            newValue = package.value(key).toString();
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

void WeatherForecastRequestPackage::createUrl(const QSharedPointer<QVariant> data)
{
    if(!getCity().isEmpty())
    {
        QMap configMap = data->toMap();
        QString url = configMap["url"].toString();
        QString key = "key=" + configMap["apikey"].toString();
        QString query = "&q=" + getCity() + "&aqi="+ configMap["airQuaility"].toString();
        setUrl(QUrl(url+key+query));
    }
}

QString WeatherForecastRequestPackage::getCity() const
{
    return mCity;
}

void WeatherForecastRequestPackage::setCity(const QString &city)
{
    mCity = city;
}
