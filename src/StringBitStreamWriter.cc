#include "StringBitStreamWriter.h"

namespace bittools {

void StringBitStreamWriter::reset()
{
    m_target.clear();
}

void StringBitStreamWriter::write(value_type value, size_type bits)
{
    for (auto i = 0U; i < bits; ++i)
    {
        const bool isSet = (value & (1ULL << i)) != 0;
        m_target += isSet ? "1" : "0";
    }
}

auto StringBitStreamWriter::bitOffset() const -> size_type
{
    return m_target.length();
}

auto StringBitStreamWriter::target() const -> const std::string&
{
    return m_target;
}

}