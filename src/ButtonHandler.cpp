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
        m_logger.Info((String("INFO: Interrupt received on pin ") + String(m_pin)).c_str(), true);
        m_logger.ToggleLogging();
    }
}
