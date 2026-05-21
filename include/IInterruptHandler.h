#pragma once

#include <stdint.h>

struct IInterruptHandler
{
    virtual void OnInterrupt() = 0;
    virtual uint8_t GetPinNumber() = 0;
};
