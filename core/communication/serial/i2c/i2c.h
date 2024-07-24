#pragma once

#include <QObject>
#include <core/util/util.h>
#include "../serial.h"

class I2C : public SerialWiringPi
{
    Q_OBJECT
public:
    explicit I2C(QObject *parent = nullptr);
    I2C(char& i2cAddress, QString& devPath, QObject *parent = nullptr );
    virtual ~I2C();

    virtual void initSerialLine() override;

signals:

public slots:
    virtual qint16 readFromPort() override;
private:
#if WIRINGPI_USAGE
    void configurateADS1115();
#endif
    char mI2CAddress;
    QString mDevicePath;

};
