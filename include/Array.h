#pragma once

#include <stdlib.h>

template <typename T, size_t N>
class Array
{
public:
    static size_t size() { return N; }

    // Item access
    T &operator[](size_t index) { return m_data[index]; }

    const T &operator[](size_t index) const { return m_data[index]; }

    // Iterators
    T *begin() { return &m_data[0]; }

    const T *begin() const { return &m_data[0]; }

    T *end() { return &m_data[N]; }

    const T *end() const { return &m_data[N]; }

    // Comparisons
    bool operator==(const Array<T, N> &rhs) const
    {
        if (this == &rhs)
        {
            return true;
        }

        for (size_t i = 0; i < N; i++)
        {
            if ((*this)[i] != rhs[i])
            {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const Array<T, N> &rhs) const
    {
        return !(*this == rhs);
    }

private:
    T m_data[N];
};
