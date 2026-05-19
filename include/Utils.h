#pragma once
#include <Arduino.h>

template <typename T>
inline Print &operator<<(Print &stream, const T &value)
{
    stream.print(value);
    return stream;
}
