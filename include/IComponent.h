#pragma once

#include "Time.h"

class IComponent
{
public:
    virtual void Setup() = 0;
    virtual void Loop() = 0;
};
