#include "i2c.h"

I2C::I2C(QObject *parent)
    : SerialWiringPi(parent)
    , mI2CAddress(ADS_1115_I2C_ADDRESS)
    , mDevicePath(i2cPath)
{
    mIsOpenFd = false;
    mFd = -1;
    initSerialLine();
}

I2C::I2C(char &i2cAddress, string &devPath, QObject *parent)
    : SerialWiringPi(parent)
    , mI2CAddress(i2cAddress)
    , mDevicePath(devPath)
{
    mIsOpenFd = false;
    mFd = -1;
    initSerialLine();
}

I2C::~I2C()
{

}
#if WIRINGPI_USAGE
qint16 I2C::readFromPort()
{
    int result = -1;
    if(isComOpened())
    {
        result= wiringPiI2CRead(mFd);
        qInfo() << "Result of i2c\t " << result;
        char *packet = reinterpret_cast<char*>( result);
        if(packet)
        emit sendPackage(packet);

    }
    else
        qInfo() << "port not opened ";
    return result;

}

void I2C::initSerialLine()
{
    mFd = wiringPiI2CSetup(mI2CAddress);
    if( mFd != -1)
    {
        mIsOpenFd = true;
        //configurateADS1115();

    }
}

void I2C::configurateADS1115()
{
    //config
    int16_t config = 1;

    wiringPiI2CWrite(mFd, config);

    //conversion
    config = 0;

}

#else
qint16 I2C::readFromPort()
{
    qInfo() << "Does not read without WringPi so far";
    int result = -1;
    return result;
}

void I2C::initSerialLine()
{
    qInfo() << "init serial Line without wiringpi";
}
#endif


