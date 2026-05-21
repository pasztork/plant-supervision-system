#pragma once

#include "Time.h"

struct ISystemComponent
{
    virtual void Setup() = 0;
    virtual void Loop() = 0;
};
