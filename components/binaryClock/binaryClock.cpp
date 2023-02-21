#include "binaryClock.h"

const int lastIndex = 7;

BinaryClock::BinaryClock(QObject *parent)
    : QObject{parent}
    , mHour(0)
    , mMinute(0)
    , mSecond(0)
{
    mDateTime = QDateTime::currentDateTime();
    mTime = mDateTime.time();

    mBinaryHour = QList<bool>(8, false);
    mBinaryMinute = QList<bool>(8, false);
    mBinarySecond = QList<bool>(8, false);

    connect(&mTimer, &QTimer::timeout, this, &BinaryClock::timeChanged);
    mTimer.setInterval(1000);
    mTimer.start(1000);
    InitClock();
}

BinaryClock::~BinaryClock()
{
    disconnect(&mTimer, &QTimer::timeout, this, &BinaryClock::timeChanged);
}

void BinaryClock::timeChanged()
{
    mTime = QTime::currentTime();
    updateHour();
    updateMinute();
    updateSecond();
}

const QList<bool> BinaryClock::binaryHour() const
{
    return mBinaryHour;
}

const QList<bool> BinaryClock::binaryMinute() const
{
    return mBinaryMinute;
}

const QList<bool> BinaryClock::binarySecond() const
{
    return mBinarySecond;
}

int BinaryClock::convertBCD(int &timeUnit)
{
    return ((timeUnit/10*16) + timeUnit %10);
}

void BinaryClock::updateHour()
{
    if(mHour != mTime.hour())
    {
        mHour = mTime.hour();
        int hour = convertBCD(mHour);
        for(int i = 0; i < mBinaryHour.size(); i++)
            mBinaryHour[lastIndex-i] = 0x01 & (hour >> i);
        emit binaryHourChanged();
    }

}

void BinaryClock::updateMinute()
{
    if(mMinute != mTime.minute())
    {
        mMinute = mTime.minute();
        int minute = convertBCD(mMinute);
        for(int i = 0; i < mBinaryMinute.size(); i++)
            mBinaryMinute[lastIndex-i] = 0x01 & (minute >> i);
        emit binaryMinuteChanged();
    }
}

void BinaryClock::updateSecond()
{
    int second = mTime.second();
    second = convertBCD(second);
    for(int i = 0; i < mBinarySecond.size(); i++)
    {
        mBinarySecond[lastIndex-i] = 0x01 & (second >> i);
    }

    emit binarySecondChanged();
}

void BinaryClock::InitClock()
{

    updateHour();
    updateMinute();
    updateSecond();
}
