#pragma once

class Logger
{
public:
    void Info(const char *message, bool forceWrite = false);
    void Error(const char *message, bool forceWrite = false);
    void ToggleLogging();

private:
    bool m_loggingEnabled = true;
};
