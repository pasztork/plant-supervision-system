#pragma once

#include <stdint.h>

#include "IInterruptHandler.h"
#include "Logger.h"

class ButtonHandler : public IInterruptHandler
{
public:
    ButtonHandler(uint8_t pin, Logger &logger);
    ~ButtonHandler() = default;

    void OnInterrupt() override;
    uint8_t GetPinNumber() override { return m_pin; }

private:
    uint8_t m_pin;
    Logger &m_logger;
    static const unsigned long DEBOUNCE_TIME_MS = 200; // Debounce time in milliseconds
};
