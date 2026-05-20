#pragma once

#include <stdint.h>

class IInterruptHandler
{
public:
    virtual void OnInterrupt() = 0;
    virtual uint8_t GetPinNumber() = 0;
};
