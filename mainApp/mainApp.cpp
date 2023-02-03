#include "mainApp.h"

MainApp::MainApp(QObject *parent)
    :QObject(parent)
{
    mBinClock = make_unique<BinaryClock>();
}

MainApp::MainApp(const int& w, const int& h, QObject *parent)
    : QObject(parent)
    , mWidth(w)
    , mHeight(h)
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

const int MainApp::width() const
{
    return mWidth;
}

const int MainApp::height() const
{
    return mHeight;
}
