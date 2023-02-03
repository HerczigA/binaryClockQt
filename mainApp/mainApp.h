#pragma once

#include <QObject>
#include <binaryClock.h>
#include <memory.h>
#include <QString>

using namespace std;

class MainApp : public QObject
{
    Q_OBJECT
    Q_PROPERTY(BinaryClock* binClock READ binClock CONSTANT)
    Q_PROPERTY(QString test READ test CONSTANT)

public:
    explicit MainApp(QObject *parent = nullptr);
    ~MainApp();
    BinaryClock* binClock() const;
    QString test() const;

private:

    unique_ptr<BinaryClock> mBinClock;
};

