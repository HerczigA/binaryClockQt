#include "wateringsystem.h"

#ifndef HIGH
    #define HIGH 1
#endif

#ifndef LOW
    #define LOW 0
#endif

WateringSystem::WateringSystem(int wateringPin, QObject *parent)
    : QObject{parent}
    , mMinMoistureLevel(30)
    , mPumpPin(wateringPin)
    , mWateringSystemState(WaterinSystemState::UnknownState)
    , mMoistureState(MoistureState::UnknownMoisture)
{
    init();
}

WateringSystem::WateringSystem(int wateringPin, int minMoistureLevel, QObject *parent)
    : QObject{parent}
    , mMinMoistureLevel(minMoistureLevel)
    , mPumpPin(wateringPin)
    , mWateringSystemState(WaterinSystemState::UnknownState)
    , mMoistureState(MoistureState::UnknownMoisture)
{
    init();
}

WateringSystem::~WateringSystem()
{
    for(auto& connection : mConnections)
        disconnect(connection);
}

const uint8_t WateringSystem::moistureLevel() const
{
    return mMoistureLevel;
}

const uint8_t WateringSystem::minMoistureLevel() const
{
    return mMinMoistureLevel;
}

const uint8_t WateringSystem::waterLevel() const
{
    return mWaterLevel;
}

const uint8_t WateringSystem::minWaterLevel() const
{
    return mMinWaterLevel;
}

void WateringSystem::setMoistureLevel(const uint8_t &level)
{
    if(mMoistureLevel != level)
    {
        mMoistureLevel = level;
        emit moistureLevelChanged();
    }
}

void WateringSystem::setMinMoistureLevel(const uint8_t &level)
{
    if(mMinMoistureLevel != level)
    {
        mMinMoistureLevel = level;
        emit minMoistureLevelChanged();
    }
}

void WateringSystem::setWaterLevel(const uint8_t &level)
{
    if(mWaterLevel != level)
    {
        mWaterLevel = level;
        emit waterLevelChanged();
    }
}

void WateringSystem::setMinWaterLevel(const uint8_t &level)
{
    if(mMinWaterLevel != level)
    {
        mMinWaterLevel = level;
        emit minWaterLevelChanged();
    }
}

const WateringSystem::WaterinSystemState WateringSystem::waterLevelState() const
{
    return mWateringSystemState;
}


void WateringSystem::setMoistureState(const MoistureState& state)
{
    if(mMoistureState != state)
    {
        mMoistureState = state;
        emit moistureStateChanged();
    }
}

void WateringSystem::setWaterLevelState(const WaterinSystemState& state)
{
    if(mWateringSystemState != state)
    {
        mWateringSystemState = state;
        emit waterLevelStateChanged();
    }
}

const WateringSystem::MoistureState WateringSystem::moistureState() const
{
    return mMoistureState;
}

void WateringSystem::checkMoistureLevel()
{
    //read data from i2c
    uint8_t result = 0; // i2cRead();
    setMoistureLevel(result);
    if(mMoistureLevel <= mMinMoistureLevel)
    {
        setMoistureState(MoistureState::Dry);
        startWatering();
    }
    else if (mMinMoistureLevel < mMoistureLevel && mMoistureLevel <= mMinMoistureLevel + thresHoldPercentage)
    {
        setMoistureState(MoistureState::NearToDry);
    }
    else
    {
        setMoistureState(MoistureState::Wet);
    }
}

void WateringSystem::startWatering()
{
    if(mTimer.isActive())
        mTimer.stop();

    if(mWateringSystemState != WaterinSystemState::WaterLevelUnderMin)
    {
        mTimer.start();
        digitalWrite(mPumpPin, HIGH);
    }
}

void WateringSystem::stopWatering()
{
    digitalWrite(mPumpPin, LOW);
}

void WateringSystem::receivedConfig(MainAppComponents::Types type, Properties settings)
{
    if(type == MainAppComponents::Types::WateringSystem)
    {
        bool ok = false;
        mProps = settings;
        mMinWaterLevel = mProps["minWaterLevel"].toInt(&ok);
        if(!ok)
            mMinWaterLevel = 0;

        ok = false;
        mMinMoistureLevel = mProps["minMoistureLevel"].toInt(&ok);
        if(!ok)
            mMinMoistureLevel = 0;

        ok = false;
        mTimer.setInterval(mProps["timerInterval"].toInt(&ok));
        if(!ok)
            mTimer.setInterval(5000);

        ok = false;
        mPumpPin = mProps["pumpPin"].toInt(&ok);
        if(!ok)
            mPumpPin = -1;
        else
        {
            pinMode(mPumpPin, OUTPUT);
            digitalWrite(mPumpPin, LOW);
        }

    }
}

void WateringSystem::init()
{

    mConnections += connect(&mTimer, &QTimer::timeout, this, &WateringSystem::stopWatering);
    mConnections += connect(this, &WateringSystem::moistureLevelChanged, this, &WateringSystem::checkMoistureLevel);
    mConnections += connect(this, &WateringSystem::waterLevelChanged, this, &WateringSystem::calculateWaterLevel);
    mConnections += connect(this, &WateringSystem::minMoistureLevelChanged, this, &WateringSystem::checkMoistureLevel);
    mConnections += connect(this, &WateringSystem::minWaterLevelChanged, this, &WateringSystem::calculateWaterLevel);
}

void WateringSystem::calculateWaterLevel()
{
    if(mWaterLevel <= mMinWaterLevel)
    {
        mWateringSystemState = WaterinSystemState::WaterLevelUnderMin;
    }
    else if(mWaterLevel < mMinWaterLevel + thresHoldPercentage)
    {
        mWateringSystemState = WaterinSystemState::WaterLevelNearToMin;
    }
    else
    {
        mWateringSystemState = WaterinSystemState::Ready;
    }
}
