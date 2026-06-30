#include "DHT11Component.h"
#include "Utils.h"

DHT11Component::DHT11Component(uint8_t pin, Logger &logger, unsigned long cycleInterval)
    : m_dht(pin, DHT11), m_logger(logger), m_cycleInterval(cycleInterval), m_lastMeasurement{0, 0, 0} {}

void DHT11Component::Setup() { m_dht.begin(); }

void DHT11Component::Loop(unsigned long currentMillis)
{
    static unsigned long lastMeasurementMillis = 0;
    static char temperatureBuffer[10];
    static char humidityBuffer[10];
    static char heatIndexBuffer[10];
    if (currentMillis - lastMeasurementMillis >= m_cycleInterval)
    {
        m_lastMeasurement.m_temperature = m_dht.readTemperature();
        m_lastMeasurement.m_humidity = m_dht.readHumidity();

        if (isnan(m_lastMeasurement.m_humidity) || isnan(m_lastMeasurement.m_temperature))
        {
            m_logger.Error("Invalid sensor readings!");
            return;
        }

        m_lastMeasurement.m_heatIndex = m_dht.computeHeatIndex(m_lastMeasurement.m_temperature, m_lastMeasurement.m_humidity);

        m_logger.Info(false, "Temperature: %s°C, Humidity: %s%%, Heat Index: %s°C",
                      dtostrf(m_lastMeasurement.m_temperature, 1, 2, temperatureBuffer),
                      dtostrf(m_lastMeasurement.m_humidity, 1, 2, humidityBuffer),
                      dtostrf(m_lastMeasurement.m_heatIndex, 1, 2, heatIndexBuffer));
        lastMeasurementMillis = currentMillis;
    }
}
