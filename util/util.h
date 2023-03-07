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


using namespace std;
using SettingMap = QMap<QString, QVariant>;

const QString weatherApiUrl = QString("http://weatherapi.com");
const QString weatherApiUrls = QString("https://weatherapi.com");

namespace MainAppComponents
{
    enum Types{
        UNKNOWN,
        WEATHERFORECAST,
        NEWS,
        ALL
    };
}
