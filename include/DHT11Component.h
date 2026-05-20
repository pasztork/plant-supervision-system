#pragma once

#include <DHT.h>

#include "IComponent.h"

class DHT11Component : public IComponent
{
public:
    struct Measurement
    {
        float m_temperature;
        float m_humidity;
        float m_heatIndex;
    };

    DHT11Component(uint8_t pin);
    ~DHT11Component() = default;

    void Setup() override;
    void Loop() override;
    inline const Measurement &GetLastMeasurement() const { return m_lastMeasurement; }

private:
    DHT m_dht;
    Measurement m_lastMeasurement;
};
