#include "mainApp.h"

MainApp::MainApp(QObject *parent)
    :QObject(parent)
{
    mBinClock = make_unique<BinaryClock>();
}


MainApp::~MainApp()
{
    mBinClock.reset();
}

BinaryClock *MainApp::binClock() const
{
    return mBinClock.get();
}

QString MainApp::test() const
{
    return QString("yolo");
}
