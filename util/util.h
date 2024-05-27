#pragma once
#include <memory>
#include <QObject>
#include <QQuickItem>
#include <QList>
#if QT_VERSION < QT_VERSION_CHECK(6, 3, 0)
    #include <QVector>
#endif
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
        WateringSystem,

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
            void setProps(Properties& props){
                mProps = props;
            }
            const MainAppComponents::Operation getRequestType() const
            {
                return mRequestType;
            }

        protected:
            Properties mProps;
            MainAppComponents::Operation  mRequestType;

    };
}
