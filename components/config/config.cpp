#include "config.h"
#include <QGuiApplication>
#include "moc_config.cpp"

Config::Config(QObject *parent )
    : QSettings{SystemScope, "MainApp","mainApp", parent}
{
    mConfigParts.insert("WeatherForecast", MainAppComponents::Types::WeatherForecast);
    mConfigParts.insert("Position", MainAppComponents::Types::Position);
    qInfo() << "Look for config file at " << fileName();

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
    Properties props;
    for(auto& group : groups)
    {
        beginGroup(group);
        QStringList keys = childKeys();
        for(auto &key : keys)
            props.insert( key, value(key));

        endGroup();
        mConfig.insert(group, props);
        emit sendData(mConfigParts[group], props);
        props.clear();
    }
}
