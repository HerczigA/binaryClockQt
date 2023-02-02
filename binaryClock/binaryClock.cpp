#include "binaryClock.h"

BinaryClock::BinaryClock(QObject *parent)
    : QObject{parent}

{
    mDateTime = QDateTime::currentDateTime();
    mTime = mDateTime.time();
    mDate = mDateTime.date();
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

void BinaryClock::updateHour()
{
    if(mHour != mTime.hour())
    {
        const uint8_t hour = mTime.hour();
        for(int i = 0; i < mBinaryHour.size(); i++)
            mBinaryHour[i] = 0x01 & (hour >> i);
        emit binaryHourChanged();
    }

}

void BinaryClock::updateMinute()
{
    if(mMinute != mTime.minute())
    {
        mMinute = mTime.minute();
        for(int i = 0; i < mBinaryMinute.size(); i++)
            mBinaryMinute[i] = 0x01 & (mMinute >> i);
        emit binaryMinuteChanged();
    }
}

void BinaryClock::updateSecond()
{
    const int second = mTime.second();
    for(int i = 0; i < mBinarySecond.size(); i++)
        mBinarySecond[i] = 0x01 & (second >> i);

    emit binarySecondChanged();
}

void BinaryClock::InitClock()
{
    mHour = mTime.hour();
    mMinute = mTime.minute();
    mSecond = mTime.second();
    updateHour();
    updateMinute();
    updateSecond();
}
