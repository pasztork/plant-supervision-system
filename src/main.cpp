#include <Arduino.h>
#include <DHT.h>

#include "State.h"
#include "Utils.h"

const int LED_PIN = 13;
const int DHT_PIN = 2;

DHT dht(DHT_PIN, DHT11);

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    dht.begin();
    Serial.begin(9600);
    Serial.println("Plant Supervision System Initialized!");
    
    // TODO: Investigate interrupts and millis() for the Arduino
    // attachInterrupt(digitalPinToInterrupt(DHT_PIN), []()
    //                 { Serial << F("Current state: ") << State::Measuring << F("\n"); }, CHANGE);
}

void loop()
{
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    float heatIndex = dht.computeHeatIndex(temperature, humidity, false);

    if (isnan(humidity) || isnan(temperature))
    {
        Serial << F("Current state: ") << State::Error << F("\n");
        delay(2000);
        return;
    }

    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    delay(1000);

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print("°C, Humidity: ");
    Serial.print(humidity);
    Serial.print("%, Heat Index: ");
    Serial.print(heatIndex);
    Serial.println("°C");

    Serial.println("System Health: OK");
}
