#pragma once
#include <QObject>
#if WIRINGPI_USAGE
    #include <wiringPi.h>
    #include <wiringPiI2C.h>
#endif

#define ADS_1115_I2C_ADDRESS 0x48

class SerialCom : public QObject
{
    Q_OBJECT
public:
    explicit SerialCom(QObject *parent = nullptr): QObject(parent){}
    virtual ~SerialCom(){}
    virtual void initSerialLine() = 0;
    const bool isComOpened() const { return mIsOpenFd;}
signals:
    void sendPackage(char* package);

protected:
    qint16 mFd;
    bool mIsOpenFd;
    void *buffer;


private:

};


class SerialWiringPi : public SerialCom
{
    Q_OBJECT
public:
    explicit SerialWiringPi(QObject *parent = nullptr)
        : SerialCom(parent)
    {

    }
    ~SerialWiringPi() {}
    //virtual void initSerialLine() = 0;
    virtual qint16 readFromPort() = 0;

signals:

protected:
    qint16 mFd;
    bool mIsOpenFd;
};
