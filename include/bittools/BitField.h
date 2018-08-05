#pragma once

namespace bittools {

/**
* Describes a bit field contained within a bit string.
* @tparam Width width of the field in bits
* @tparam Pos position of the fields, starting from the LSB
* @tparam T type of the bit field
*/
template<unsigned FieldWidth, unsigned FieldStart, typename T = unsigned>
struct BitField
{
    using value_type = T;
    static constexpr auto Width = FieldWidth;
    static constexpr auto Start = FieldStart;
    static constexpr auto End = Start + Width;
};

}