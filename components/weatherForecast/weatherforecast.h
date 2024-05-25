#pragma once
#include <util.h>

class WeatherForecast : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString date READ date NOTIFY dataChanged)
    Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY dataChanged)
    Q_PROPERTY(QString temperature READ temperature WRITE setTemperature NOTIFY dataChanged)
    Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY dataChanged)
    QML_ANONYMOUS

    public:
        class WeatherProps : public MainAppComponents::Props
        {
            public:
                WeatherProps()
                {
                    mRequestType=MainAppComponents::Operation::GET;
                }
                const QString getRawUrl() override;
                const QString getCity() const;
                void setCity(QString newCity);
        };

        explicit WeatherForecast(QObject *parent = nullptr);
        WeatherForecast(const WeatherForecast &other);
        ~WeatherForecast();
        Q_INVOKABLE void requestDataFromUI();
        void updateLocation();
        void sendRequestWeatherData();

        QString date() const;
        QString location() const;
        QString icon() const;
        QString temperature() const;

        void setDate(const QDate &value);
        void setLocation(const QString &value);
        void setIcon(const QString &value);
        void setTemperature(const QString &value);

    signals:
        void dataChanged();
        void requestSignal(MainAppComponents::Props * props, int sourceType);
        void requestLocation();

    public slots:
        void requestArrived();
        void receivedData(MainAppComponents::PropertiesPacket packet);
        void receivedConfig(MainAppComponents::Types type, Properties data);
        void cityUpdated(QString var);

    private:

        QVector<QMetaObject::Connection> mConnections;

        QString mTemperature;
        QString mDayOfTheWeek;
        QString mWeatherIcon;

        QDate mDate;
        WeatherProps mProps;
};

