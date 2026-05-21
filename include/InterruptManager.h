#pragma once

#include <stdint.h>

#include "Array.h"
#include "IInterruptHandler.h"

class InterruptManager
{
public:
    static bool RegisterInterruptHandler(IInterruptHandler *handler);

private:
    static void HandleInterrupt0();
    static void HandleInterrupt1();

private:
    static const uint8_t MAX_INTERRUPTS = 2; // There are only 2 external interrupts on the Arduino Uno
    static Array<IInterruptHandler *, MAX_INTERRUPTS> s_interruptHandlers;
};
