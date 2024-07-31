#pragma once

#include <QObject>
#include <QString>
#include <QDate>

namespace qml
{


class WeatherForecastModel : public QObject
{
    Q_OBJECT
    // Q_PROPERTY(QString date READ date NOTIFY dataChanged)
    Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY dataChanged)
    Q_PROPERTY(QString temperature READ temperature WRITE setTemperature NOTIFY dataChanged)
    // Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY dataChanged)

    public:
        
        explicit WeatherForecastModel(QObject *parent = nullptr);
        Q_INVOKABLE void requestDataFromUI();
        
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
        void requestData();

    public slots:
        void onDateReceived(const QDate& date);
        void onTemperatureReceived(const QString& temperature);
        void onLocationReceived(const QString& location);
        void onIconReceived(const QString& icon);

    private:

        QString mTemperature;
        QString mLocation;
        QString mWeatherIcon;
        QDate mDate;
};

}
