#pragma once

#include <core/binaryClock/binaryClock.h>
#include <ui/Model/ListModel/ListModel.h>
#include <QObject>
#include <QList>

namespace qml
{

class BinarySecondModel : public QObject
{
    
    Q_OBJECT
    Q_PROPERTY(bool second READ second CONSTANT)
    public:
        bool second() const { return mSecond; }
    private:
        bool mSecond;
};

class BinaryClockModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<bool> binaryHour READ  binaryHour NOTIFY binaryHourChanged)
    Q_PROPERTY(QList<bool> binaryMinute READ binaryMinute NOTIFY binaryMinuteChanged)
    Q_PROPERTY(QAbstractListModel* listModel READ listModel CONSTANT)

    public:
        explicit BinaryClockModel (QObject *parent = nullptr);
        ~BinaryClockModel ();
        const QList<bool> binaryHour() const;
        const QList<bool> binaryMinute() const;
        QAbstractListModel* listModel() const { return mBinarySecond; }
        void setBinaryHour(const QList<bool>& hour);
        void setBinaryMinute(const QList<bool>& minute);
        // void setBinarySecond(const QList<bool>& second);

    signals:
        void binaryHourChanged();
        void binaryMinuteChanged();
        // void binarySecondChanged();
        void updateWeather();
        void turnNewDay();

    public slots:
        void receivedTimeUnits(const BinaryClock::BinaryClockUnit unit, const QList<bool> result);
        
    private:
        inline void checkIsNewDay();
        QList<bool> mBinaryHour;
        QList<bool> mBinaryMinute;
        AbstractListModel<bool>* mBinarySecond;
};

}
