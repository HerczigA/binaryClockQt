#pragma once

#include <core/util/util.h>
#include <QSettings>

class Config : public QSettings
{
    Q_OBJECT
public:
    explicit Config(QObject *parent = nullptr);

    void readConfig();
    bool configFileIsExist();

signals:
    void sendData(MainAppComponents::Types type, Properties  data);
public slots:
    void writeConfig();
private:
    void getSubGroups(QStringList &groups);
    QStringList mAllKeys;
    QMap<QString, Properties> mConfig;
    QMap<QString, MainAppComponents::Types> mConfigParts;
};