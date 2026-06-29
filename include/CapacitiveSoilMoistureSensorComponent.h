#pragma once

#include <stdint.h>

#include "ISystemComponent.h"
#include "Logger.h"

class CapacitiveSoilMoistureSensorComponent : public ISystemComponent
{
public:
    struct Measurement
    {
        uint16_t m_moisturePercentage;
    };

    struct PinConfiguration
    {
        uint8_t m_analogPin;
        uint8_t m_digitalPin;
    };

    struct CalibrationValues
    {
        uint16_t m_dryValue;
        uint16_t m_wetValue;
    };

    struct StateTiming
    {
        unsigned long m_prepareSensorMillis;
        unsigned long m_measurementIntervalMillis;
    };

    explicit CapacitiveSoilMoistureSensorComponent(PinConfiguration pinConfig, Logger &logger, CalibrationValues calibrationValues = {1023, 0}, StateTiming stateTiming = {1000, 4000});
    ~CapacitiveSoilMoistureSensorComponent() = default;

    void Setup() override;
    void Loop(unsigned long currentMillis) override;
    inline const Measurement &GetLastMeasurement() const { return m_lastMeasurement; }

private:
    enum class State : uint8_t
    {
        SensorOff,
        PrepareSensor,
        Measure,
        TurnOffSensor,
    };

    PinConfiguration m_pinConfig;
    CalibrationValues m_calibrationValues;
    StateTiming m_stateTiming;
    Measurement m_lastMeasurement;
    State m_state;
    Logger& m_logger;
};
