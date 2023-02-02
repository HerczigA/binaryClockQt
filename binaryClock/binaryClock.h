#pragma once


#include <QObject>
#include <QQuickItem>
#include <QDateTime>
#include <QList>
#include <QTimer>
#include <QDebug>

class BinaryClock : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<bool> binaryHour READ binaryHour NOTIFY binaryHourChanged)
    Q_PROPERTY(QList<bool> binaryMinute READ binaryMinute NOTIFY binaryMinuteChanged)
    Q_PROPERTY(QList<bool> binarySecond READ binarySecond NOTIFY binarySecondChanged)

    public:
        explicit BinaryClock (QObject *parent = nullptr);
        ~BinaryClock ();

    signals:
        void binaryHourChanged();
        void binaryMinuteChanged();
        void binarySecondChanged();


    private slots:
        void timeChanged();

    private:
        const QList<bool> binaryHour() const;
        const QList<bool> binaryMinute() const;
        const QList<bool> binarySecond() const;
        void updateHour();
        void updateMinute();
        void updateSecond();
        void InitClock();
        QDateTime mDateTime;
        QTime mTime;
        QDate mDate;
        QList<bool> mBinaryHour;
        QList<bool> mBinaryMinute;
        QList<bool> mBinarySecond;
        int mHour;
        int mMinute;
        int mSecond;
        QTimer mTimer;
};



