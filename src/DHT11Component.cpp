#include "DHT11Component.h"
#include "Utils.h"

DHT11Component::DHT11Component(uint8_t pin, Logger &logger) : m_dht(pin, DHT11), m_logger(logger), m_lastMeasurement{0, 0, 0} {}

void DHT11Component::Setup()
{
    m_dht.begin();
}

void DHT11Component::Loop(unsigned long currentMillis)
{
    m_lastMeasurement.m_temperature = m_dht.readTemperature();
    m_lastMeasurement.m_humidity = m_dht.readHumidity();

    if (isnan(m_lastMeasurement.m_humidity) || isnan(m_lastMeasurement.m_temperature))
    {
        m_logger.Error("ERROR: Invalid sensor readings!");
        return;
    }

    m_lastMeasurement.m_heatIndex = m_dht.computeHeatIndex(m_lastMeasurement.m_temperature, m_lastMeasurement.m_humidity);

    m_logger.Info((String("INFO: Temperature: ") + String(m_lastMeasurement.m_temperature) + String("°C, Humidity: ") + String(m_lastMeasurement.m_humidity) + String("%, Heat Index: ") + String(m_lastMeasurement.m_heatIndex) + String("°C")).c_str());
}
