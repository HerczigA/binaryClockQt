#pragma once
#include <util.h>


struct WeatherProps{
    enum Attributes
    {
        Unknown = 0,
        Url,
        City,
        Apikey,
        AirQuality,
        Days,
        Alert,
        Error = -1
    };

    QString mUrl;
    QString mCity;
    QString mApiKey;
    QString mAirQuality;
    QString mDays;
    QString mAlert;
    MainAppComponents::Operation  mRequestType;

    WeatherProps()
        : mUrl("https://api.weatherapi.com/v1/current.json?")
        , mCity("&q=Budapest")
        , mApiKey("key=")
        , mAirQuality("&aqi=no")
        , mDays("&days=5")
        , mAlert("&alerts=yes")
        , mRequestType(MainAppComponents::Operation::GET) //get for http
    {

    }
    void setUrl(QString url){mUrl = url;}
    void setCity(QString city){mCity = "&q="+ city ;}
    void setDays(QString days){mDays= "&days="+ days ;}
    void setApiKey(QString key){mApiKey = "key="+ key ;}
    void setAlert(QString alertOn){mAlert = "&alerts="+ alertOn;}
    void setAirQuality(QString airQuality){mAirQuality= "&aqi="+ airQuality;}
    void setRequestType(MainAppComponents::Operation &type){mRequestType = type;}
    const QString getCity(){return mCity;}
    const QString getDays(){return mDays;}
    const QString getApiKey(){return mApiKey;}
    const QString getAlert(){return mAlert;}
    const MainAppComponents::Operation  getRequestType(){return mRequestType;}
    const QString getRawUrl(){ return mUrl + mApiKey + mCity + mAirQuality; }
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
    ~WeatherForecast();
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
    void requestArrived();
    void receivedData(MainAppComponents::Types type, QByteArray rawData);
    void receivedConfig(MainAppComponents::Types type, SettingMap  data);
    void cityUpdated(QString city);



private:

    QVector<QMetaObject::Connection> mConnections;


    QString mCityLocation;
    QString mTemperature;
    QString mDayOfTheWeek;
    QString mWeatherIcon;

    QMap<int, QString> mPropMap = {
        {WeatherProps::Attributes::Url, "url"},
        {WeatherProps::Attributes::City, "city"},
        {WeatherProps::Attributes::Apikey, "apikey"},
        {WeatherProps::Attributes::AirQuality, "airQuality"},
        {WeatherProps::Attributes::Days, "days"},
        {WeatherProps::Attributes::Alert, "alerts"}
    };

    QDate mDate;
    WeatherProps mProps;
};

