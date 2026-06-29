#pragma once

class Period
{
public:
    Period() : m_start(0), m_end(0) {}
    inline unsigned long Duration() const { return m_end - m_start; }

private:
    unsigned long m_start;
    unsigned long m_end;
};
