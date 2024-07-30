#include "binaryClockModel.h"

const int lastIndex = 7;

qml::BinaryClockModel::BinaryClockModel(QObject *parent)
    : QObject{parent}
    , mBinaryHour(8,false)
    , mBinaryMinute(8,false)
    , mBinarySecond(8,false)
{
}

qml::BinaryClockModel::~BinaryClockModel()
{
}

const QList<bool> qml::BinaryClockModel::binaryHour() const
{
    return mBinaryHour;
}

const QList<bool> qml::BinaryClockModel::binaryMinute() const
{
    return mBinaryMinute;
}

const QList<bool> qml::BinaryClockModel::binarySecond() const
{
    return mBinarySecond;
}

void qml::BinaryClockModel::receivedTimeUnits(const BinaryClock::BinaryClockUnit unit, const QList<bool> result)
{
    if(unit == BinaryClock::BinaryClockUnit::Hour)
    {
        setBinaryHour(result);
    }
    else if(unit == BinaryClock::BinaryClockUnit::Minute)
    {
        setBinaryMinute(result);
    }
    else
    {
        setBinarySecond(result);
    }
}

void qml::BinaryClockModel::setBinaryHour(const QList<bool>& hour)
{
    if(mBinaryHour != hour)
    {
        mBinaryHour = hour;
        emit binaryHourChanged();
    }
}

void qml::BinaryClockModel::setBinaryMinute(const QList<bool>& minute)
{
    if(mBinaryMinute != minute)
    {
        mBinaryMinute = minute;
        emit binaryMinuteChanged();
    }
}

void qml::BinaryClockModel::setBinarySecond(const QList<bool>& second)
{
    if(mBinarySecond != second)
    {
        mBinarySecond = second;
        emit binarySecondChanged();
    }
}
