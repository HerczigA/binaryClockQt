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

        // BinaryClockUnit& operator++(BinaryClockUnit& unit) {
        //     unit = static_cast<BinaryClockUnit>(static_cast<std::underlying_type_t<BinaryClockUnit>>(unit) + 1);
        //     return c;
        // }

        explicit BinaryClock (QObject *parent = nullptr);
        ~BinaryClock ();

    signals:
        void timeUnitChanged(const BinaryClockUnit unit, const QList<bool> result);

    private slots:
        void updateTimeUnits();

    private:
        int convertBCD(int& sec);
        int getActualTimeUnit(BinaryClockUnit unit);
        int mHour;
        int mMinute;
        int mSecond;
        QTimer mTimer;
};

