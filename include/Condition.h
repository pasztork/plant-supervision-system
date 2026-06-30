#pragma once

struct Condition 
{
    virtual bool IsSatisfied() const = 0;
};
