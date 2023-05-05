#include "config.h"
#include <QGuiApplication>

Config::Config(QObject *parent )
    : QSettings{SystemScope, "MainApp","mainApp", parent}
{
    mConfigParts.insert("WeatherForecast", MainAppComponents::Types::WEATHERFORECAST);
    mConfigParts.insert("Position", MainAppComponents::Types::POSITION);
    qDebug()<< this->fileName();
}

void Config::readConfig()
{
    if(configFileIsExist())
    {
        sync();
        mAllKeys = allKeys();
        if(mAllKeys.empty())
            return;
        QStringList subGroups = childGroups();
        getSubGroups(subGroups);
    }
//    else
//    {
//        exit in case there will be fatal error
//        for mandatory function
//    }
}

bool Config::configFileIsExist()
{
    return QFile::exists(fileName());
}

void Config::writeConfig()
{
    for(auto& key : mConfigParts.keys())
    {
        beginGroup(key);
        for(const auto &confKey: mConfig.keys())
            setValue(confKey, mConfig.value(confKey));
        endGroup();
        sync();
    }
}

void Config::getSubGroups(QStringList &groups)
{
    SettingMap  settings;
    for(auto& group : groups)
    {
        beginGroup(group);
        QStringList keys = childKeys();
        for(auto &key : keys)
            settings.insert( key, value(key));

        endGroup();

        mConfig.insert(group, settings);
        emit sendData(mConfigParts[group], settings);
        settings.clear();
    }
}
