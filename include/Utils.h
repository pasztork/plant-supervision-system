#pragma once
#include <Arduino.h>
#include <avr/sleep.h>

template <typename T>
inline Print &operator<<(Print &stream, const T &value)
{
    stream.print(value);
    return stream;
}

inline void TODO(const char *message)
{
    noInterrupts();
    Serial << F("[TODO] ") << message << F("\n");
    Serial.flush();
    while (true);
}
