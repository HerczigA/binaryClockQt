#pragma once
#include <memory>
#include <QObject>
#include <QQuickItem>
#include <QList>
#include <QVector>
#include <QTimer>
#include <QDebug>
#include <QVariant>
#include <QJsonObject>
#include <QJsonDocument>
#include <QStringList>
#include <QMap>
#include <QFile>


using namespace std;
using SettingMap = QMap<QString, QVariant>;

const QString weatherApiUrls = QString("https://weatherapi.com");

namespace MainAppComponents
{
    enum Types{
        UNKNOWN,
        WeatherForecast,
        Position,
        NEWS,
        ALL
    };
    enum Operation
    {
        UNKNOWN_OPERATION,
        HEAD,
        GET,
        PUT,
        POST,
        DELETE,
        CUSTOM

    };

}
