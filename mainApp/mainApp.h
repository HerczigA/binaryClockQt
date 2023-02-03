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
    Q_PROPERTY(int width READ width CONSTANT)
    Q_PROPERTY(int height READ height CONSTANT)

public:
    explicit MainApp(QObject *parent = nullptr);
    MainApp(const int& w, const int& h, QObject *parent = nullptr);
    ~MainApp();
    BinaryClock* binClock() const;
    const int width() const;
    const int height() const;

private:
    int mWidth;
    int mHeight;
    unique_ptr<BinaryClock> mBinClock;
};

