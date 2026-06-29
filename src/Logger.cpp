#include <Arduino.h>

#include "Logger.h"
#include "Utils.h"

void Logger::Info(const char *message, bool forceWrite)
{
    if (m_loggingEnabled || forceWrite)
    {
        Serial << F("INFO: ") << message << F("\n");
    }
}

void Logger::Error(const char *message, bool forceWrite)
{
    if (m_loggingEnabled || forceWrite)
    {
        Serial << F("ERROR: ") << message << F("\n");
    }
}

void Logger::ToggleLogging()
{
    m_loggingEnabled = !m_loggingEnabled;
    Serial << F("INFO: Logging ") << (m_loggingEnabled ? F("enabled") : F("disabled")) << F("\n");
}
