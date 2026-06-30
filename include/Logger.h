#pragma once

#include <stdarg.h>

class Logger
{
public:
    void Info(const char *message, ...);
    void Info(bool forceWrite, const char *message, ...);
    void Error(const char *message, ...);
    void Error(bool forceWrite, const char *message, ...);
    void ToggleLogging();

private:
    void WriteMessage(const char *level, bool forceWrite, const char *message, va_list args);

private:
    bool m_loggingEnabled = true;
};
