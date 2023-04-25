#include "config.h"
#include <QGuiApplication>

Config::Config(QObject *parent )
    : QSettings{SystemScope, "MainApp","mainApp", parent}
{
    mConfigParts.insert(MainAppComponents::Types::WEATHERFORECAST, "WeatherForecast");
    qDebug()<< this->fileName();
}

void Config::readConfig()
{
    if(configFileIsExist())
    {
        sync();
        mAllKeys = allKeys();
        if(mAllKeys .empty())
            emit configEmpty();

        QStringList subGroups = childGroups();
        digDeeper(subGroups);
    }

}

bool Config::configFileIsExist()
{
    return QFile::exists(fileName());
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
