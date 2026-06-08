#pragma once

#include <Arduino.h>

#include "Array.h"
#include "IInterruptHandler.h"
#include "InterruptManager.h"
#include "ISystemComponent.h"
#include "Utils.h"

template <size_t N>
class PlantSupervisionSystem : ISystemComponent
{
public:
    void Setup() override
    {
        noInterrupts();
        Serial.begin(9600);
        SetupComponents();
        SetupInterrupts();
        m_initialized = true;
        Serial << F("INFO: Plant Supervision System Setup Complete!\n");
        interrupts();
    }

    void Loop() override
    {
        if (!m_initialized)
        {
            Serial << F("ERROR: Plant Supervision System is not initialized!\n");
            return;
        }

        for (size_t i = 0; i < m_components.size() && m_components[i] != nullptr; i++)
        {
            m_components[i]->Loop();
        }

        Serial << F("INFO: System Health: OK\n");
    }

    bool AddComponent(ISystemComponent *component)
    {
        bool foundSlot = false;
        for (size_t i = 0; i < m_components.size() && !foundSlot; i++)
        {
            if (m_components[i] == nullptr)
            {
                m_components[i] = component;
                foundSlot = true;
            }
        }

        if (!foundSlot)
        {
            Serial << F("ERROR: Failed to add component: No available slot!\n");
        }

        return false;
    }

    bool AddInterruptHandler(IInterruptHandler *handler)
    {
        bool foundSlot = false;
        for (size_t i = 0; i < m_interruptHandlers.size() && !foundSlot; i++)
        {
            if (m_interruptHandlers[i] == nullptr)
            {
                m_interruptHandlers[i] = handler;
                foundSlot = true;
            }
        }

        if (!foundSlot)
        {
            Serial << F("ERROR: Failed to add interrupt handler: No available slot!\n");
        }

        return false;
    }

private:
    void SetupComponents()
    {
        for (size_t i = 0; i < m_components.size() && m_components[i] != nullptr; i++)
        {
            m_components[i]->Setup();
        }
    }

    void SetupInterrupts()
    {
        for (size_t i = 0; i < m_interruptHandlers.size() && m_interruptHandlers[i] != nullptr; i++)
        {
            InterruptManager::RegisterInterruptHandler(m_interruptHandlers[i]);
        }
    }

private:
    bool m_initialized = false;
    Array<ISystemComponent *, N> m_components;
    Array<IInterruptHandler *, 2> m_interruptHandlers;
};
