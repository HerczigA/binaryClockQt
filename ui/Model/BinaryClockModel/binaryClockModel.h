#pragma once

#include <core/binaryClock/binaryClock.h>

#include <QObject>
#include <QList>

namespace qml
{

class BinaryClockModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<bool> binaryHour READ  binaryHour NOTIFY binaryHourChanged)
    Q_PROPERTY(QList<bool> binaryMinute READ binaryMinute NOTIFY binaryMinuteChanged)
    Q_PROPERTY(QList<bool> binarySecond READ binarySecond NOTIFY binarySecondChanged)

    public:
        explicit BinaryClockModel (QObject *parent = nullptr);
        ~BinaryClockModel ();
        const QList<bool> binaryHour() const;
        const QList<bool> binaryMinute() const;
        const QList<bool> binarySecond() const;
        void setBinaryHour(const QList<bool>& hour);
        void setBinaryMinute(const QList<bool>& minute);
        void setBinarySecond(const QList<bool>& second);

    signals:
        void binaryHourChanged();
        void binaryMinuteChanged();
        void binarySecondChanged();
        void updateWeather();
        void turnNewDay();

    public slots:
        void receivedTimeUnits(const BinaryClock::BinaryClockUnit unit, const QList<bool> result);
        
    private:
        inline void checkIsNewDay();
        QList<bool> mBinaryHour;
        QList<bool> mBinaryMinute;
        QList<bool> mBinarySecond;
};

}
