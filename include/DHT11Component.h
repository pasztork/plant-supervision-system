#pragma once

#include <DHT.h>

#include "ISystemComponent.h"
#include "Logger.h"

class DHT11Component : public ISystemComponent
{
public:
    struct Measurement
    {
        float m_temperature;
        float m_humidity;
        float m_heatIndex;
    };

    explicit DHT11Component(uint8_t pin, Logger &logger);
    ~DHT11Component() = default;

    void Setup() override;
    void Loop(unsigned long currentMillis) override;
    inline const Measurement &GetLastMeasurement() const { return m_lastMeasurement; }

private:
    DHT m_dht;
    Logger &m_logger;
    Measurement m_lastMeasurement;
};
