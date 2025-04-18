#include "config.h"

#include <QFile>
#include <QDebug>

Config::ConfigPacket::ConfigPacket()
{
}

Config::ConfigPacket::ConfigPacket(const ConfigPacket &ConfigPacket)
{
    *this = ConfigPacket;
}

Config::ConfigPacket::ConfigPacket(const Config::Types &opType, const ConfigMap &configMap)
    : mConfigMap(configMap)
    , mConfigType(opType)
{
}

Config::Config(QObject *parent )
    : QSettings{QSettings::IniFormat, QSettings::SystemScope, "MainApp","mainApp", parent}
{
    this->setFallbacksEnabled(false);
    qInfo() << "Look for config file at " << fileName();
}

void Config::readConfig()
{

    if(configFileIsExist())
    {
        sync();
        if(allKeys().empty())
            return;
        getSubGroups(childGroups());
    }
    else
    {
        qInfo() << "Config file not found or empty";
    }
}

bool Config::configFileIsExist()
{
    return QFile::exists(fileName());
}

void Config::writeConfig()
{
    for(auto& packet : mConfigPackets)
    {
        auto getEnumString= [&](Types t){
            QMetaEnum metaEnum = QMetaEnum::fromType<Config::Types>();
            const char* enumString = metaEnum.valueToKey(static_cast<int>(t));
            return QString(enumString);
        };
        QString key = getEnumString(packet->mConfigType);
        beginGroup(key);
        for(const auto &confKey: packet->mConfigMap.keys())
        {
            setValue(confKey, packet->mConfigMap.value(confKey));
        }
        endGroup();
        sync();
    }
}

void Config::getSubGroups(QStringList &&groups)
{
    ConfigMap setting;
    for(auto& group : groups)
    {
        beginGroup(group);
        QStringList keys = childKeys();
        for(auto &key : keys)
            setting.insert( key, value(key));
        endGroup();
        std::shared_ptr<Config::ConfigPacket> packet = createPacket(group, setting);
        if(packet)
        {
            mConfigPackets.append(packet);
            emit sendConfigProps(packet);
        }
        setting.clear();
    }
}

std::shared_ptr<Config::ConfigPacket> Config::createPacket(const QString& enumString,const ConfigMap& setting)
{
    std::shared_ptr<Config::ConfigPacket> packetPtr;
    bool ok = false;
    QMetaEnum metaEnum = QMetaEnum::fromType<Config::Types>();
    int enumValue = metaEnum.keyToValue(enumString.toStdString().c_str(), &ok);
    if(ok)
    {
        return std::make_shared<ConfigPacket>(static_cast<Config::Types>(enumValue), setting);
    }
    else
    {
        qDebug()<< "meta system could not realize the enum type or to enum's key";
        return nullptr;
    }
}
