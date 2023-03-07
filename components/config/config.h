#pragma once

#include <util.h>
#include <QSettings>

class Config : public QSettings
{
    Q_OBJECT
public:
    explicit Config(QObject *parent = nullptr);


    void getValue(int&);
    void getValue(QString&);
    void readConfig();


signals:
    void configEmpty();
    void sendData(MainAppComponents::Types type, SettingMap  data);
public slots:
    void writeConfig(MainAppComponents::Types type, SettingMap  props);
private:
    void digDeeper(QStringList &groups);
    QStringList mAllKeys;
    SettingMap  mSettings;
    QMap<MainAppComponents::Types, QString> mConfigParts;
};

