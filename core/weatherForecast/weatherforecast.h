#pragma once

#include <core/communication/network/network.h>
#include <core/config/config.h>
#include <memory>


class WeatherForecastRequestPackage : public NetworkRequestPackage
{
    Q_OBJECT
    public:
        explicit WeatherForecastRequestPackage(QObject *parent=nullptr);
        ~WeatherForecastRequestPackage();
        void createUrl(const QSharedPointer<QVariant> data = nullptr) override;
        void updateUrl(const QString& location);
        QString getLocation() const;
        void setLocation(const QString& location);
    private:
        QString mLocation;
};

class WeatherForecast : public QObject
{
    Q_OBJECT

    public:
        explicit WeatherForecast(QObject *parent = nullptr);
        ~WeatherForecast();
        void updateLocation();
        void sendRequestWeatherData();

    signals:
        void requestPackage(QSharedPointer<NetworkRequestPackage> package);
        void requestLocation();
        void sendTemperature(const QString& temperature);
        void sendIcon(const QString& icon);
        void sendLocation(const QString& location);

    public slots:
        void requestArrived();
        void receivedRequestResult(QByteArray& result);
        void receivedConfig(const std::shared_ptr<Config::ConfigPacket> packet);
        void locationReceived(const QString& city);

    private:
        QString mTemperature;
        QString mWeatherIcon;
        QSharedPointer<WeatherForecastRequestPackage> mWeatherForecastRequestPackage;
};

