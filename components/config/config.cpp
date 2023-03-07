#include "config.h"
#include <QGuiApplication>

const QString configFile= "./config.ini";

Config::Config(QString config, QObject *parent )
    : QSettings{"HerczigDocLtd","mainApp", parent}
    , mConfigFile(config)

{
    if(config == "")
        mConfigFile = QGuiApplication::applicationDirPath() + configFile;
    qDebug()<< this->fileName();

}

void Config::readConfig()
{
    sync();
    QStringList keyList = this->allKeys();
    if(keyList.empty())
    {


        emit configEmpty();
    }
    QStringList subKeys;

    for(auto & it : keyList)
    {
        qDebug()<< value(it);
        if(it.contains("WeatherForecast"))
        {
            beginGroup("WeatherForecast");
            subKeys =  childKeys();
            for(auto& it : subKeys)
            {
                mSettings.insert(it, value(it));
            }


        }
        emit sendData(MainAppComponents::Types::WEATHERFORECAST, mSettings);
    }

}
