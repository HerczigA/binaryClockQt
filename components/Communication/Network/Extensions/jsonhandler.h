#pragma once
#include <util.h>

class JsonHandler : public QObject
{
    Q_OBJECT
public:
    explicit JsonHandler(QObject *parent = nullptr);
    MainAppComponents::PropertiesPacket processRawData(MainAppComponents::Types type, QByteArray rawData);


signals:
    void requestImageDownloading(const QUrl);

private:
    void processWeatherComponents(QJsonObject &object, MainAppComponents::PropertiesPacket & packet);
    void processPositionComponents(QJsonObject &object, MainAppComponents::PropertiesPacket & packet);


};

