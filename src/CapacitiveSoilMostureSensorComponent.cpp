#include "CapacitiveSoilMoistureSensorComponent.h"
#include "Utils.h"

CapacitiveSoilMoistureSensorComponent::CapacitiveSoilMoistureSensorComponent(PinConfiguration pinConfig, Logger &logger, CalibrationValues calibrationValues, StateTiming stateTiming)
    : m_pinConfig(pinConfig), m_logger(logger), m_calibrationValues(calibrationValues), m_stateTiming(stateTiming), m_lastMeasurement{0}, m_state(State::SensorOff) {}

void CapacitiveSoilMoistureSensorComponent::Setup()
{
    pinMode(m_pinConfig.m_digitalPin, OUTPUT);
    digitalWrite(m_pinConfig.m_digitalPin, LOW); // Ensure the sensor is powered off initially
}

void CapacitiveSoilMoistureSensorComponent::Loop(unsigned long currentMillis)
{
    static unsigned long lastMeasureMillis = currentMillis;
    static unsigned long turningOnMillis = currentMillis;
    static uint16_t rawValue = 0;

    switch (m_state)
    {
    case State::SensorOff:
        if (currentMillis - lastMeasureMillis >= m_stateTiming.m_measurementIntervalMillis)
        {
            digitalWrite(m_pinConfig.m_digitalPin, HIGH);
            turningOnMillis = currentMillis;
            m_state = State::PrepareSensor;
        }
        break;
    case State::PrepareSensor:
        if (currentMillis - turningOnMillis >= m_stateTiming.m_prepareSensorMillis)
        {
            m_state = State::Measure;
        }
        break;
    case State::Measure:
        rawValue = analogRead(m_pinConfig.m_analogPin);
        m_logger.Info("Raw Moisture Sensor Value: %u", rawValue);

        m_lastMeasurement.m_moisturePercentage = map(rawValue, m_calibrationValues.m_dryValue, m_calibrationValues.m_wetValue, 0, 100);

        // 0 is completely dry, 100 is completely wet.
        m_logger.Info("Soil Moisture Level: %u%%", m_lastMeasurement.m_moisturePercentage);

        lastMeasureMillis = currentMillis;
        m_state = State::TurnOffSensor;
        break;
    case State::TurnOffSensor:
        digitalWrite(m_pinConfig.m_digitalPin, LOW);
        m_state = State::SensorOff;
        break;
    default:
        break;
    }
}
