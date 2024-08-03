#pragma once

#include <core/communication/network/network.h>
#include <core/config/config.h>
#include <memory>


class WeatherForecastRequestPackage : public NetworkRequestPackage
{
    Q_OBJECT
    public:
        explicit WeatherForecastRequestPackage(QObject *parent = nullptr);
        ~WeatherForecastRequestPackage();
        void createUrl(const QSharedPointer<QVariant> data) override;
        QString getCity() const;
        void setCity(const QString& city);
    private:
        QString mCity;
};

class WeatherForecast : public QObject
{
    Q_OBJECT

    public:
        explicit WeatherForecast(QObject *parent = nullptr);
        ~WeatherForecast();
        Q_INVOKABLE void requestDataFromUI();
        void updateLocation();
        void sendRequestWeatherData();

    signals:
        void requestPackage(QSharedPointer<NetworkRequestPackage> package);
        void requestLocation();
        void sendTemperature(const QString& temperature);
        void sendIcon(const QString& icon);

    public slots:
        void requestArrived();
        void receivedRequestResult(QByteArray& result);
        void receivedConfig(const std::shared_ptr<Config::ConfigPacket> packet);
        void cityReceived(QSharedPointer<QString> city);

    private:
        QString mTemperature;
        QString mWeatherIcon;
        QSharedPointer<WeatherForecastRequestPackage> mWeatherForecastRequestPackage;
};

