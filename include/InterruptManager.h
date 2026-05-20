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
    static const uint8_t MAX_INTERRUPTS = 2;
    static Array<IInterruptHandler *, MAX_INTERRUPTS> s_interruptHandlers;
};
