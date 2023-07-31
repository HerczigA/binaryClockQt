#pragma once
#include <util.h>

const uint8_t thresHoldPercentage = 10;
class WateringSystem : public QObject
{
    enum WaterinSystemState{
        UnknownState,
        Ready,
        WaterLevelNearToMin,
        WaterLevelUnderMin,
    };

    enum MoistureState{
        UnknownMoisture,
        Wet,
        NearToDry,
        Dry
    };

    Q_OBJECT
    Q_PROPERTY(uint8_t moistureLevel READ moistureLevel WRITE setMoistureLevel NOTIFY moistureLevelChanged)
    Q_PROPERTY(uint waterLevel READ waterLevel WRITE setWaterLevel NOTIFY waterLevelChanged)

    Q_PROPERTY(uint8_t minWaterLevel READ minWaterLevel WRITE setMinWaterLevel NOTIFY minWaterLevelChanged)
    Q_PROPERTY(uint8_t minMoistureLevel READ minMoistureLevel WRITE setMinMoistureLevel NOTIFY minMoistureLevelChanged)


    Q_PROPERTY(WaterinSystemState waterLevelState READ waterLevelState WRITE setWaterLevelState NOTIFY waterLevelStateChanged)
    Q_PROPERTY(MoistureState moistureState READ moistureState WRITE setMoistureState NOTIFY moistureStateChanged)

public:
    explicit WateringSystem(int wateringPin, QObject *parent = nullptr);
    WateringSystem(int wateringPin, int minMoistureLevel, QObject *parent = nullptr);
    ~WateringSystem();
    const uint8_t moistureLevel() const;
    void setMoistureLevel(const uint8_t& level);
    const uint8_t minMoistureLevel() const;
    void setMinMoistureLevel(const uint8_t& level);

    const uint8_t waterLevel() const;
    void setWaterLevel(const uint8_t& level);

    const uint8_t minWaterLevel() const;
    void setMinWaterLevel(const uint8_t& level);

    const WaterinSystemState waterLevelState() const;
    void setWaterLevelState(const WaterinSystemState& state);

    const MoistureState moistureState() const;
    void setMoistureState(const MoistureState& state);

signals:
    void moistureLevelChanged();
    void minMoistureLevelChanged();
    void waterLevelChanged();
    void minWaterLevelChanged();
    void waterLevelStateChanged();
    void moistureStateChanged();

public slots:
    Q_INVOKABLE void checkMoistureLevel();
    //Q_INVOKABLE void checkMoistureLevel();
    Q_INVOKABLE void startWatering();
    Q_INVOKABLE void stopWatering();
    void receivedConfig(MainAppComponents::Types type, Properties settings);

private:
    void init();
    void calculateWaterLevel();

    uint8_t mMinMoistureLevel;
    uint8_t mMoistureLevel;
    uint8_t mPumpPin;
    uint8_t mWaterLevel;
    uint8_t mMinWaterLevel;
    WaterinSystemState mWateringSystemState;
    MoistureState mMoistureState;
    QString mI2CPort;
    char mI2CSlaveAddress;

    Properties mProps;
    QList<QMetaObject::Connection> mConnections;
    QTimer mTimer;

};
