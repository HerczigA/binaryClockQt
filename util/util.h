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

using namespace std;

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
