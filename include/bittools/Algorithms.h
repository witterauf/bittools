#pragma once

namespace bittools {

/// Calculates $\lfloor\operatorname{ld} x\rfloor$.
constexpr auto ld(unsigned long long x) -> unsigned long long
{
    return x <= 1ULL ? 0ULL : 1ULL + ld(x >> 1ULL);
}

/// Calculates $\lceil\operatorname{ld} x\rceil$.
constexpr auto numberOfBits(unsigned long long x) -> unsigned long long
{
    return x <= 1ULL ? 0ULL : 1ULL + ld(x - 1ULL);
}

/// Calculates $\lceil x/8\rceil$ (the number of bytes a bit string of length bits needs).
constexpr auto inFullBytes(unsigned long long bits) -> unsigned long long
{
    return (bits >> 3) + ((bits & 0b111) != 0 ? 1 : 0);
}

/// Calculates $\lceil x/alignment\rceil$.
constexpr auto alignAt(unsigned long long toAlign, unsigned long long alignment) -> unsigned long long
{
    return toAlign % alignment == 0
        ? toAlign
        : toAlign + alignment - (toAlign % alignment);
}

constexpr auto wordCount(unsigned long long bits, unsigned long long width) -> unsigned long long
{
    return bits % width == 0
        ? bits / width
        : bits / width + 1;
}

/// Sign-extends a signed integer with width FromWidth to a signed integer T.
/// @tparam FromWidth bit width the value is stored in
/// @tparam T type to sign-extend to
/// @param value value to sign-extend
template<unsigned FromWidth, typename T>
T signExtend(T value)
{
    static_assert(FromWidth >= 1);
    T signBit = static_cast<T>(1ULL << (FromWidth - 1));
    T mask = static_cast<T>(~((1ULL << FromWidth) - 1));
    return static_cast<T>((value & signBit) != 0 ? (value | mask) : value);
}

}