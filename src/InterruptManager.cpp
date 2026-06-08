#include <Arduino.h>

#include "InterruptManager.h"
#include "Utils.h"

Array<IInterruptHandler *, InterruptManager::MAX_INTERRUPTS> InterruptManager::s_interruptHandlers = {};

void InterruptManager::HandleInterrupt0()
{
    if (s_interruptHandlers[0] != nullptr)
    {
        s_interruptHandlers[0]->OnInterrupt();
    }
}

void InterruptManager::HandleInterrupt1()
{
    if (s_interruptHandlers[1] != nullptr)
    {
        s_interruptHandlers[1]->OnInterrupt();
    }
}

bool InterruptManager::RegisterInterruptHandler(IInterruptHandler *handler)
{
    uint8_t interruptIndex = handler->GetPinNumber() - 2; // Assuming interrupts are on pins 2 and 3

    if (interruptIndex >= MAX_INTERRUPTS)
    {
        Serial << F("ERROR: Invalid interrupt pin number: ") << handler->GetPinNumber() << F("\n");
        return false;
    }

    s_interruptHandlers[interruptIndex] = handler;
    attachInterrupt(digitalPinToInterrupt(handler->GetPinNumber()), HandleInterrupt0, RISING);
    return true;
}
