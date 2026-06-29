#include "ButtonHandler.h"
#include "CapacitiveSoilMoistureSensorComponent.h"
#include "DHT11Component.h"
#include "PlantSupervisionSystem.h"

const unsigned long MEASUREMENT_INTERVAL = 1000;
unsigned long g_currentMillis = 0;
unsigned long g_lastMeasurementTime = 0;

PlantSupervisionSystem<2> g_plantSupervisionSystem;

namespace SystemStorage
{
    ButtonHandler g_buttonHandler(2, g_plantSupervisionSystem.GetLogger());
    DHT11Component g_dht11(7, g_plantSupervisionSystem.GetLogger());
    CapacitiveSoilMoistureSensorComponent g_capacitiveSoilMoistureSensor({0, 4}, g_plantSupervisionSystem.GetLogger(), {558, 208}, {1000, 4000});
}

void setup()
{
    g_currentMillis = millis();
    g_lastMeasurementTime = g_currentMillis;

    g_plantSupervisionSystem.AddComponent(&SystemStorage::g_dht11);
    g_plantSupervisionSystem.AddComponent(&SystemStorage::g_capacitiveSoilMoistureSensor);
    g_plantSupervisionSystem.AddInterruptHandler(&SystemStorage::g_buttonHandler);
    g_plantSupervisionSystem.Setup();
}

void loop()
{
    g_currentMillis = millis();

    if (g_currentMillis - g_lastMeasurementTime >= MEASUREMENT_INTERVAL)
    {
        g_lastMeasurementTime = g_currentMillis;
        g_plantSupervisionSystem.Loop(g_currentMillis);
    }
}
