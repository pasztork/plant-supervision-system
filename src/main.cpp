#include "ButtonHandler.h"
#include "CapacitiveSoilMoistureSensorComponent.h"
#include "DHT11Component.h"
#include "PlantSupervisionSystem.h"

PlantSupervisionSystem<2> g_plantSupervisionSystem(5000);

namespace SystemStorage
{
    ButtonHandler g_buttonHandler(2, g_plantSupervisionSystem.GetLogger());
    DHT11Component g_dht11(7, g_plantSupervisionSystem.GetLogger(), 10000);
    CapacitiveSoilMoistureSensorComponent g_capacitiveSoilMoistureSensor({0, 4}, g_plantSupervisionSystem.GetLogger(), {558, 208}, {1000, 4000});
}

void setup()
{
    g_plantSupervisionSystem.AddComponent(&SystemStorage::g_dht11);
    g_plantSupervisionSystem.AddComponent(&SystemStorage::g_capacitiveSoilMoistureSensor);
    g_plantSupervisionSystem.AddInterruptHandler(&SystemStorage::g_buttonHandler);
    g_plantSupervisionSystem.Setup();
}

void loop() { g_plantSupervisionSystem.Loop(); }
