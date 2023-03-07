#include "config.h"
#include <QGuiApplication>

Config::Config(QObject *parent )
    : QSettings{"HerczigDocLtd","mainApp", parent}
{
    mConfigParts.insert(MainAppComponents::Types::WEATHERFORECAST, "WeatherForecast");
}

void Config::readConfig()
{
    sync();
    mAllKeys = this->allKeys();
    if(mAllKeys .empty())
        emit configEmpty();

    QStringList subGroups = childGroups();
    digDeeper(subGroups);
}

void Config::writeConfig(MainAppComponents::Types type, SettingMap  props)
{
    beginGroup(mConfigParts.value(type));
    for(const auto &key: props.keys())
        setValue(key, props.value(key));
    endGroup();
    sync();
}

void Config::digDeeper(QStringList &groups)
{

    for(auto& group : groups)
    {
        beginGroup(group);
        QStringList subGroups = childGroups();
        if(subGroups.size() != 0)
            digDeeper(subGroups);
        QStringList keys = childKeys();
        for(auto &key : keys)
            mSettings.insert(key, value(key));

        endGroup();
        emit sendData(mConfigParts.key(group), mSettings);
    }
}
