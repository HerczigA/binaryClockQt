#pragma once
#include <memory>
#include <QObject>
// #include <QQuickItem>
#include <QList>
#include <QTimer>
#include <QDebug>
#include <QVariant>
#include <QJsonObject>
#include <QJsonDocument>
#include <QStringList>
#include <QMap>
#include <QFile>
#include <QList>
#include <QtGlobal>

using Properties = QMap<QString, QVariant>;
const QString i2cPath = "/dev/i2c-1";

namespace MainAppComponents
{
    enum Types{
        Unknown,
        WeatherForecast,
        Position,
        Icon,
        All
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

    struct PropertiesPacket
    {
        Types type;
        Properties props;
        PropertiesPacket() : type(Types::Unknown){}
    };

    class Props
    {
        public:
            virtual ~Props(){}
            virtual const QString getRawUrl() = 0;
            void setProps(const Properties& props);
            const MainAppComponents::Operation getRequestType() const;
        protected:
            Properties mProps;
            MainAppComponents::Operation  mRequestType;

    };
}
