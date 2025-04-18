#pragma once

#include <QObject>
#include <QMap>
#include <QSettings>
#include <QMetaType>
#include <QMetaEnum>

using ConfigMap = QMap<QString, QVariant>;

class Config : public QSettings
{
    Q_OBJECT
public:
    explicit Config(QObject *parent = nullptr);
    enum class Types{
            Unknown = -1,
            WeatherForecast,
            Position,
            All
    };
    Q_ENUM(Types);

    struct ConfigPacket
    {
        ConfigPacket();
        ConfigPacket(const ConfigPacket& configPacket);
        ConfigPacket(const Config::Types& opType, const ConfigMap& configMap);
        ~ConfigPacket(){}  
        ConfigMap mConfigMap;
        Config::Types  mConfigType;
    };

    void readConfig();
    bool configFileIsExist();
    template<typename T>
    static const QString parseEnumKeyToString(T metaEnumKey)
    {
        QMetaEnum metaEnum = QMetaEnum::fromType<T>();
        const char* enumString = metaEnum.valueToKey(static_cast<int>(metaEnumKey));
        return QString(enumString);
    }
    template<typename T>
    static T parseEnumStringToKey(const QString& enumString)
    {
        bool ok = false;
        QMetaEnum metaEnum = QMetaEnum::fromType<T>();
        int enumValue = metaEnum.keyToValue(enumString.toStdString().c_str(), &ok);
        if(ok)
        {
            return static_cast<T>(enumValue);
        }
        return static_cast<T>(-1);
    }

signals:
    void sendConfigProps(const std::shared_ptr<Config::ConfigPacket> settingData);
public slots:
    void writeConfig();

private:
    void getSubGroups(QStringList &&groups);
    std::shared_ptr<Config::ConfigPacket> createPacket(const QString& enumString,const ConfigMap& setting);
    QList<std::shared_ptr<ConfigPacket>> mConfigPackets;
};

Q_DECLARE_METATYPE(Config::ConfigPacket)
Q_DECLARE_METATYPE(std::shared_ptr<Config::ConfigPacket>)
