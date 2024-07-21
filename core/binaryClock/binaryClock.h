#pragma once

#include <core/util/util.h>

class BinaryClock : public QObject
{
    Q_OBJECT
    //CONSTANT only without write and notify

    Q_PROPERTY(QList<bool> binaryHour READ  binaryHour NOTIFY binaryHourChanged)
    Q_PROPERTY(QList<bool> binaryMinute READ binaryMinute NOTIFY binaryMinuteChanged)
    Q_PROPERTY(QList<bool> binarySecond READ binarySecond NOTIFY binarySecondChanged)

    public:
        explicit BinaryClock (QObject *parent = nullptr);
        ~BinaryClock ();

    signals:
        void binaryHourChanged();
        void binaryMinuteChanged();
        void binarySecondChanged();
        void updateWeather();


    private slots:
        void timeChanged();

    private:
        const QList<bool> binaryHour() const;
        const QList<bool> binaryMinute() const;
        const QList<bool> binarySecond() const;
        int convertBCD(int& sec);
        // void updateBinaryUnit();
        void updateHour();
        void updateMinute();
        void updateSecond();
        void InitClock();
        QDateTime mDateTime;
        QTime mTime;
        QList<bool> mBinaryHour;
        QList<bool> mBinaryMinute;
        QList<bool> mBinarySecond;
        int mHour;
        int mMinute;
        int mSecond;
        QTimer mTimer;
};

