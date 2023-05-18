#include "jsonhandler.h"

JsonHandler::JsonHandler(QObject *parent)
    : QObject{parent}
{

}

MainAppComponents::PropertiesPacket JsonHandler::processRawData(MainAppComponents::Types type, QByteArray rawData)
{
    MainAppComponents::PropertiesPacket packet;
    QJsonParseError result;
    QJsonObject obj;
    QJsonDocument document = QJsonDocument::fromJson(rawData, &result);
    if(result.error == QJsonParseError::NoError && !document.isEmpty())
    {
        if(document.isObject())
        {
            obj = document.object();
            if(type == MainAppComponents::Types::Position)
                processPositionComponents(obj, packet);
            else
                processWeatherComponents(obj, packet);
        }

    }
    else
        qInfo()<< "Error at json parsing object side";
    return packet;
}

void JsonHandler::processWeatherComponents(QJsonObject &object, MainAppComponents::PropertiesPacket &packet)
{
    QJsonValue value;
    value = object.value("current");
    packet.type = MainAppComponents::Types::WeatherForecast;

    if(!value.isNull())
    {
        QString newValue = value["temp_c"].toVariant().toString();
        packet.props.insert("temperature", QVariant(newValue));
        newValue = value["condition"]["icon"].toString();
        if(!newValue.isEmpty() && newValue.contains("//"))
        {
            newValue = "http:" + newValue; //.right(newValue.size()-2);
//            "//cdn.weatherapi.com/weather/64x64/day/296.png"
            packet.props.insert("icon", QVariant(newValue));
//            QUrl url(newValue);
//            emit requestImageDownloading(url);
        }

    }
}

void JsonHandler::processPositionComponents(QJsonObject &object, MainAppComponents::PropertiesPacket &packet)
{
    packet.type = MainAppComponents::Types::Position;
    QJsonValue value = object.value("data");
    if(!value.isNull())
    {
        QString location = value[0]["locality"].toVariant().toString();
        packet.props.insert("city", QVariant(location));
    }
}
