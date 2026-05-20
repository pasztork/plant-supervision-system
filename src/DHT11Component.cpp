#include "DHT11Component.h"
#include "Utils.h"

DHT11Component::DHT11Component(uint8_t pin) : m_dht(pin, DHT11) {}

void DHT11Component::Setup()
{
    m_dht.begin();
}

void DHT11Component::Loop()
{
    m_lastMeasurement.m_temperature = m_dht.readTemperature();
    m_lastMeasurement.m_humidity = m_dht.readHumidity();

    if (isnan(m_lastMeasurement.m_humidity) || isnan(m_lastMeasurement.m_temperature))
    {
        Serial << F("[ERROR] Invalid sensor readings!\n");
        return;
    }

    m_lastMeasurement.m_heatIndex = m_dht.computeHeatIndex(m_lastMeasurement.m_temperature, m_lastMeasurement.m_humidity);

    Serial << F("[DHT11] Temperature: ") << m_lastMeasurement.m_temperature << F("°C, Humidity: ") << m_lastMeasurement.m_humidity
           << F("%, Heat Index: ") << m_lastMeasurement.m_heatIndex << F("°C\n");
}
