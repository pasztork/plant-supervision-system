#pragma once

#include <Arduino.h>

#include "Array.h"
#include "IInterruptHandler.h"
#include "InterruptManager.h"
#include "ISystemComponent.h"
#include "Logger.h"
#include "Utils.h"

template <size_t N>
class PlantSupervisionSystem
{
public:
    PlantSupervisionSystem(unsigned long cycleInterval)
        : m_components(), m_interruptHandlers(), m_cycleInterval(cycleInterval),
          m_lastMeasurementMillis(0), m_currentMillis(0) {}

    void Setup()
    {
        noInterrupts();
        Serial.end();
        Serial.begin(9600);
        SetupComponents();
        SetupInterrupts();
        m_initialized = true;
        m_currentMillis = millis();
        m_lastMeasurementMillis = m_currentMillis;
        m_logger.Info("Plant Supervision System Setup Complete!");
        interrupts();
    }

    void Loop()
    {
        if (!m_initialized)
        {
            m_logger.Error("Plant Supervision System not initialized!");
            return;
        }

        m_currentMillis = millis();

        if (m_currentMillis - m_lastMeasurementMillis >= m_cycleInterval)
        {
            for (size_t i = 0; i < m_components.size() && m_components[i] != nullptr; i++)
            {
                m_components[i]->Loop(m_currentMillis);
            }

            m_logger.Info("System Health: OK");
            m_lastMeasurementMillis = m_currentMillis;
        }
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
            m_logger.Error("Failed to add component: No available slot!");
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
            m_logger.Error("Failed to add interrupt handler: No available slot!");
        }

        return false;
    }

    inline Logger &GetLogger() { return m_logger; }

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
    Logger m_logger;
    Array<ISystemComponent *, N> m_components;
    Array<IInterruptHandler *, 2> m_interruptHandlers;
    const unsigned long m_cycleInterval;
    unsigned long m_lastMeasurementMillis;
    unsigned long m_currentMillis;
};
