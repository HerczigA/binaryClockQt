#pragma once

#include <QGeoPositionInfoSource>
#include <QGeoLocation>
#include <QGeoAddress>

#include <util.h>


struct WeatherProps{
    QString url;
    QString city;
    QString apiKey;
    QString airQuality;
    QString days;
    QString alert;
    int requestType;

    WeatherProps()
        : url("https://api.weatherapi.com/v1/current.json?")
        , city("&q=Budapest")
        , apiKey("key=")
        , airQuality("&aqi=no")
        , days("&days=5")
        , alert("&alerts=yes")
        , requestType(2) //get for http
    {

    }
    void setCity(QString city){this->city = "&q="+ city ;}
    void setDays(QString days){this->days= "&days="+ days ;}
    void setApiKey(QString key){this->apiKey = "key="+ key ;}
    void setAlert(QString alertOn){this->alert = "&alerts="+ alertOn;}
    void setRequestType(int &type){this->requestType = type;}
};

class WeatherForecast : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString date READ date WRITE setDate NOTIFY dataChanged)
    Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY dataChanged)
    Q_PROPERTY(QString temperature READ temperature WRITE setTemperature NOTIFY dataChanged)
    Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY dataChanged)
    QML_ANONYMOUS

public:
    explicit WeatherForecast(QObject *parent = nullptr);
    WeatherForecast(const WeatherForecast &other);
    Q_INVOKABLE void updateLocation();
    void sendRequestWeatherData();

    QString date() const;
    QString location() const;
    QString icon() const;
    QString temperature() const;

    void setDate(const QString &value);
    void setLocation(const QString &value);
    void setIcon(const QString &value);
    void setTemperature(const QString &value);

signals:
    void dataChanged();
    void requestSignal(void * props, int sourceType);

public slots:
    void receivedData(MainAppComponents::Types type, QByteArray rawData);
    void receivedConfig(MainAppComponents::Types type, SettingProps data);



private:
    int mWeatherStatus;
//    QString mLocation;
    QString mTemperature;
    QString mDayOfTheWeek;
    QString mWeatherIcon;

    unique_ptr<QGeoLocation> mLocation;
    unique_ptr<QGeoAddress> mAddress;
    QDate mDate;
    WeatherProps mProps;
};

