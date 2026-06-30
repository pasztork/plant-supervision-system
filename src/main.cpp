#include "ButtonHandler.h"
#include "CapacitiveSoilMoistureSensorComponent.h"
#include "DHT11Component.h"
#include "PlantSupervisionSystem.h"
#include "RelayControlledComponent.h"

PlantSupervisionSystem<3> g_plantSupervisionSystem(5000);

namespace SystemStorage
{
    DHT11Component g_dht11(7, g_plantSupervisionSystem.GetLogger(), 10000);
    CapacitiveSoilMoistureSensorComponent g_capacitiveSoilMoistureSensor({0, 4}, g_plantSupervisionSystem.GetLogger(), {570, 208}, {1000, 4000});
    RelayControlledComponent g_relayControlledComponent(8, g_plantSupervisionSystem.GetLogger(), g_capacitiveSoilMoistureSensor);
    ButtonHandler g_buttonHandler(2, g_plantSupervisionSystem.GetLogger());
}

void setup()
{
    g_plantSupervisionSystem.AddComponent(&SystemStorage::g_dht11);
    g_plantSupervisionSystem.AddComponent(&SystemStorage::g_capacitiveSoilMoistureSensor);
    g_plantSupervisionSystem.AddComponent(&SystemStorage::g_relayControlledComponent);
    g_plantSupervisionSystem.AddInterruptHandler(&SystemStorage::g_buttonHandler);
    g_plantSupervisionSystem.Setup();
}

void loop() { g_plantSupervisionSystem.Loop(); }
