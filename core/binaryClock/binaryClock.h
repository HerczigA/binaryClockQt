#pragma once

#include <QObject>
#include <QList>
#include <QTimer>


class BinaryClock : public QObject
{
    Q_OBJECT
    public:
        enum class BinaryClockUnit
        {
            Hour,
            Minute,
            Second
        };
        Q_ENUM(BinaryClockUnit);
        explicit BinaryClock (QObject *parent = nullptr);
        ~BinaryClock ();

    signals:
        void timeUnitChanged(const BinaryClockUnit unit, const QList<bool> result);

    private slots:
        void updateTimeUnits();

    private:
        inline void checkIsNewDay(const QList<bool>& hour);
        int convertBCD(int& sec);
        int getActualTimeUnit(BinaryClockUnit unit);
        int mHour;
        int mMinute;
        int mSecond;
        QTimer mTimer;
};

