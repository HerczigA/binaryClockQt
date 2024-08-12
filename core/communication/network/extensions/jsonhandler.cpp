#include "jsonhandler.h"

JsonHandler::JsonHandler(QObject *parent)
    : QObject{parent}
{

}

MainAppComponents::PropertiesPacket JsonHandler::processRawData(MainAppComponents::Types type, QByteArray rawData)
{
    MainAppComponents::PropertiesPacket packet;
    QJsonParseError result;
    QJsonDocument document = QJsonDocument::fromJson(rawData, &result);
    if(result.error == QJsonParseError::NoError && !document.isEmpty())
    {
        if(document.isObject())
        {
            QJsonObject obj = document.object();
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
            newValue = "http:" + newValue;
            packet.props.insert("icon", QVariant(newValue));
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
