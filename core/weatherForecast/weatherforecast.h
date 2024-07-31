#pragma once

#include <core/communication/network/network.h>

#include <memory>

class WeatherForecast : public QObject
{
    Q_OBJECT

    public:
        class WeatherProps : public MainAppComponents::Props
        {
            public:
                WeatherProps();
                void createUrl();
                const QUrl getUrl();
                const QString getCity() const;
                void setCity(QString newCity);
            private:
                QUrl mUrl;
                QString mCity;
        };

        explicit WeatherForecast(QObject *parent = nullptr);
        ~WeatherForecast();
        Q_INVOKABLE void requestDataFromUI();
        void updateLocation();
        void sendRequestWeatherData();

    signals:
        // void requestSignal(MainAppComponents::Props * props, int sourceType);
        void requestLocation();
        void sendTemperature(const QString& temperature);
        void sendIcon(const QString& icon);

    public slots:
        void requestArrived();
        void receivedData(MainAppComponents::PropertiesPacket packet);
        void receivedConfig(MainAppComponents::Types type, Setting setting);
        void cityUpdated(QString var);

    private:
        QString mTemperature;
        QString mDayOfTheWeek;
        QString mWeatherIcon;

        QDate mDate;
        WeatherProps mProps;
        std::unique_ptr<Network> mNetwork;
        
};

