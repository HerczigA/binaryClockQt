#include "binaryClock.h"

#include <QTime>

const int binaryTimeUnit = 7;

BinaryClock::BinaryClock(QObject *parent)
    : QObject{parent}
    , mHour(0)
    , mMinute(0)
    , mSecond(0)
{
    connect(&mTimer, &QTimer::timeout, this, &BinaryClock::updateTimeUnits);
    mTimer.setInterval(1000);
    mTimer.start();
}

BinaryClock::~BinaryClock()
{
    disconnect(&mTimer, &QTimer::timeout, this, &BinaryClock::updateTimeUnits);
}

int BinaryClock::convertBCD(int &timeUnit)
{
    return ((timeUnit/10*16) + timeUnit %10);
}

int BinaryClock::getActualTimeUnit(BinaryClockUnit unit)
{
    QTime time = QTime::currentTime();
    switch (unit)
    {
        case BinaryClockUnit::Hour:
            return time.hour();
        case BinaryClockUnit::Minute:
            return time.minute();
        case BinaryClockUnit::Second:
            return time.second();
        default:
            return 0;
    }
}

void BinaryClock::updateTimeUnits()
{
    for(int unit = 0; unit <= static_cast<int>(BinaryClockUnit::Second); unit++)
    {
        QList<bool> result(8,false);
        int timeUnit = getActualTimeUnit(static_cast<BinaryClockUnit>(unit));
        int time = convertBCD(timeUnit);
        for(int i = 0; i <= binaryTimeUnit; i++)
            result[binaryTimeUnit-i] = 0x01 & (time >> i);
        emit timeUnitChanged(static_cast<BinaryClockUnit>(unit), result);
    }
}

