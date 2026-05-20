#pragma once

class Period
{
public:
    inline unsigned long Duration() const { return m_end - m_start; }

private:
    unsigned long m_start;
    unsigned long m_end;
};
