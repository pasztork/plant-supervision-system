#pragma once

#include <stdint.h>

#include "IInterruptHandler.h"

class ButtonHandler : public IInterruptHandler
{
public:
    explicit ButtonHandler(uint8_t pin);
    ~ButtonHandler() = default;

    void OnInterrupt() override;
    uint8_t GetPinNumber() override { return m_pin; }

private:
    uint8_t m_pin;
};
