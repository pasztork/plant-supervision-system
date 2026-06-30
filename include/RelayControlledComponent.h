#pragma once

#include <stdint.h>

#include "Condition.h"
#include "ISystemComponent.h"
#include "Logger.h"

class RelayControlledComponent : public ISystemComponent
{
public:
    RelayControlledComponent(uint8_t relayPin, Logger &logger, const Condition &condition);
    ~RelayControlledComponent() = default;

    void Setup() override;
    void Loop(unsigned long currentMillis) override;

private:
    enum class State : uint8_t
    {
        Off,
        TurningOn,
        Holding,
        TurningOff,
    };

    uint8_t m_relayPin;
    Logger &m_logger;
    const Condition &m_condition;
    State m_state;
};
