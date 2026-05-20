#include "ButtonHandler.h"
#include "Utils.h"

ButtonHandler::ButtonHandler(uint8_t pin) : m_pin(pin) {}

void ButtonHandler::OnInterrupt()
{
    // Placeholder for button interrupt handling logic
    Serial << F("[ButtonHandler] Interrupt received on pin ") << m_pin << F("\n");
}
