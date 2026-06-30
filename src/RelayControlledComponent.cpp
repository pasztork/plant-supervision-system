#include <Arduino.h>

#include "RelayControlledComponent.h"

RelayControlledComponent::RelayControlledComponent(uint8_t relayPin, Logger &logger, const Condition &condition)
    : m_relayPin(relayPin), m_logger(logger), m_condition(condition), m_state(State::Off) {}

void RelayControlledComponent::Setup()
{
    pinMode(m_relayPin, OUTPUT);
    digitalWrite(m_relayPin, LOW);
}

void RelayControlledComponent::Loop(unsigned long)
{
    switch (m_state)
    {
    case State::Off:
        if (m_condition.IsSatisfied())
        {
            m_state = State::TurningOn;
        }
        break;
    case State::TurningOn:
        m_logger.Info("Activating relay on pin %u", m_relayPin);
        m_state = State::Holding;
        digitalWrite(m_relayPin, HIGH);
        break;
    case State::Holding:
        if (!m_condition.IsSatisfied())
        {
            m_state = State::TurningOff;
        }
        break;
    case State::TurningOff:
        m_logger.Info("Deactivating relay on pin %u", m_relayPin);
        m_state = State::Off;
        digitalWrite(m_relayPin, LOW);
        break;
    default:
        m_logger.Error("Unknown state in RelayControlledComponent!");
        break;
    }
}
