#pragma once

#include <QGeoPositionInfoSource>
#include <QGeoLocation>
#include <QGeoAddress>
#include <QNetworkRequest>
#include <util.h>

class WeatherForecast : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString date READ date WRITE setDate NOTIFY dataChanged)
//    Q_PROPERTY(QString weatherIcon READ weatherIcon WRITE setWeatherIcon NOTIFY dataChanged)
    Q_PROPERTY(QString weatherDescription READ weatherDescription WRITE setWeatherDescription NOTIFY dataChanged)
    Q_PROPERTY(QString temperature READ temperature WRITE setTemperature NOTIFY dataChanged)
    Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY dataChanged)
    QML_ANONYMOUS

public:
    explicit WeatherForecast(QObject *parent = nullptr);
    WeatherForecast(const WeatherForecast &other);
    Q_INVOKABLE void updateLocation();
    QString date() const;
//    QString weatherIcon() const;
    QString location() const;
    QString weatherDescription() const;
    QString temperature() const;

    void setDate(const QString &value);
    void setLocation(const QString &value);
    void setWeatherDescription(const QString &value);
    void setTemperature(const QString &value);

signals:
    void dataChanged();





private:
    int mWeatherStatus;
//    QString mLocation;
    QString mTemperature;
    QString mDayOfTheWeek;
    QString mWeatherDescription;

    unique_ptr<QGeoLocation> mLocation;
    unique_ptr<QGeoAddress> mAddress;
    QDate mDate;
};

