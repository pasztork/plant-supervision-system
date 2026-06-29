#pragma once

struct ISystemComponent
{
    virtual void Setup() = 0;
    virtual void Loop(unsigned long currentMillis) = 0;
};
