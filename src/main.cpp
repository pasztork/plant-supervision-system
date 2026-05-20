#include "ButtonHandler.h"
#include "DHT11Component.h"
#include "PlantSupervisionSystem.h"

const unsigned long MEASUREMENT_INTERVAL = 5000;
unsigned long g_lastMeasurementTime = 0;

namespace SystemStorage
{
    DHT11Component g_dht11(7);
    ButtonHandler g_buttonHandler(2);
}

PlantSupervisionSystem<1> g_plantSupervisionSystem;

void setup()
{
    g_plantSupervisionSystem.AddComponent(&SystemStorage::g_dht11);
    g_plantSupervisionSystem.AddInterruptHandler(&SystemStorage::g_buttonHandler);
    g_plantSupervisionSystem.Setup();
}

void loop()
{
    unsigned long currentTime = millis();

    if (currentTime - g_lastMeasurementTime >= MEASUREMENT_INTERVAL)
    {
        g_lastMeasurementTime = currentTime;
        g_plantSupervisionSystem.Loop();
    }
}
