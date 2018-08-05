#pragma once

#include "Algorithms.h"
#include <array>
#include <cstdint>

namespace bittools {

template<size_t Size>
class BitMap
{
public:
    void setTo(size_t index, bool value)
    {
        if (value)
        {
            set(index);
        }
        else
        {
            reset(index);
        }
    }

    void set(size_t index)
    {
        m_bitmap[wordIndex(index)] |= (1 << withinWordIndex(index));
    }

    void reset(size_t index)
    {
        m_bitmap[wordIndex(index)] &= ~(1 << withinWordIndex(index));
    }

    void toggle(size_t index)
    {
        setTo(index, !get(index));
    }

    bool get(size_t index) const
    {
        return (m_bitmap[wordIndex(index)] & withinWordIndex(index)) != 0;
    }

    bool operator[](size_t index) const
    {
        return get(index);
    }

    operator bool() const
    {
        for (auto i = 0U; i < Words; ++i)
        {
            if (m_bitmap[i] != 0)
            {
                return true;
            }
        }
        return false;
    }

private:
    static constexpr size_t WordSize = 64;
    static constexpr size_t WordCount = wordCount(Size, WordSize);

    auto wordIndex(size_t index) -> size_t
    {
        return index / WordSize;
    }

    auto withinWordIndex(size_t index) -> size_t
    {
        return index % WordSize;
    }

    std::array<uint64_t, Words> m_bitmap = { 0 };
};

}