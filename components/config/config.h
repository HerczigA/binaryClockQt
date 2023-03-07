#pragma once

#include <util.h>
#include <QSettings>

class Config : public QSettings
{
    Q_OBJECT
public:
    explicit Config(QString config, QObject *parent = nullptr);


    void getValue(int&);
    void getValue(QString&);
    void readConfig();

signals:
    void configEmpty();
    void sendData(MainAppComponents::Types type, SettingProps data);

private:

    QString mConfigFile;
    SettingProps mSettings;

};

