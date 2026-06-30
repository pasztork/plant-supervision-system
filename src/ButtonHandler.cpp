#include "ButtonHandler.h"
#include "Utils.h"

ButtonHandler::ButtonHandler(uint8_t pin, Logger &logger) : m_pin(pin), m_logger(logger) {}

void ButtonHandler::OnInterrupt()
{
    static unsigned long lastInterruptTime = 0;
    unsigned long currentInterruptTime = millis();
    if (currentInterruptTime - lastInterruptTime > DEBOUNCE_TIME_MS)
    {
        lastInterruptTime = currentInterruptTime;
        m_logger.Info(true, "Interrupt received on pin %u", m_pin);
        m_logger.ToggleLogging();
    }
}
