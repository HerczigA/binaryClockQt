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
#include <QImage>

using namespace std;
using Properties = QMap<QString, QVariant>;

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
