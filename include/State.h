#pragma once
#include <Arduino.h>

enum class State
{
    Initializing,
    Measuring,
    Logging,
    Error
};

inline const char *ToString(const State state)
{
    switch (state)
    {
    case State::Initializing:
        return "Initializing";
    case State::Measuring:
        return "Measuring";
    case State::Logging:
        return "Logging";
    case State::Error:
        return "Error";
    default:
        return "Unknown";
    }
}

inline Print &operator<<(Print &stream, State state)
{
    stream.print(ToString(state));
    return stream;
}
