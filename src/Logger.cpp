#include <Arduino.h>
#include <stdio.h>

#include "Logger.h"
#include "Utils.h"

namespace
{
    constexpr size_t LOG_BUFFER_SIZE = 256;
}

void Logger::WriteMessage(const char *level, bool forceWrite, const char *message, va_list args)
{
    if (m_loggingEnabled || forceWrite)
    {
        char buffer[LOG_BUFFER_SIZE];
        vsnprintf(buffer, sizeof(buffer), message, args);

        Serial.print(level);
        Serial.println(buffer);
    }
}

void Logger::Info(const char *message, ...)
{
    va_list args;
    va_start(args, message);
    WriteMessage("INFO: ", false, message, args);
    va_end(args);
}

void Logger::Info(bool forceWrite, const char *message, ...)
{
    va_list args;
    va_start(args, message);
    WriteMessage("INFO: ", forceWrite, message, args);
    va_end(args);
}

void Logger::Error(const char *message, ...)
{
    va_list args;
    va_start(args, message);
    WriteMessage("ERROR: ", false, message, args);
    va_end(args);
}

void Logger::Error(bool forceWrite, const char *message, ...)
{
    va_list args;
    va_start(args, message);
    WriteMessage("ERROR: ", forceWrite, message, args);
    va_end(args);
}

void Logger::ToggleLogging()
{
    m_loggingEnabled = !m_loggingEnabled;
    Info(true, "Logging %s", m_loggingEnabled ? "enabled" : "disabled");
}
