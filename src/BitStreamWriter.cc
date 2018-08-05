#include "BitStreamWriter.h"
#include "Algorithms.h"

namespace bittools {

void BitStreamWriter::writeBuffer(const uint8_t* data, size_t bits)
{
    auto const bytes = bits / 8;
    for (auto i = 0U; i < bytes; ++i)
    {
        write(data[i], 8);
    }

    auto const bitsLeft = bits % 8;
    if (bitsLeft > 0)
    {
        write(data[bytes], bitsLeft);
    }
}

MemoryBitStreamWriter::MemoryBitStreamWriter(stream_base_type* target, size_type startOffset)
    : m_target{ target }, m_offset{ startOffset } {}

auto MemoryBitStreamWriter::bitOffset() const -> size_type
{
    return m_offset;
}

void MemoryBitStreamWriter::setBitOffset(size_type offset)
{
    m_offset = offset;
}

void MemoryBitStreamWriter::setTarget(stream_base_type* target)
{
    m_target = target;
}

void MemoryBitStreamWriter::write(value_type value, size_type bits)
{
    if (bits == 0)
    {
        return;
    }

    auto byteOffset = m_offset >> 3;
    auto const bitOffset = m_offset & 0b111;

    if (bitOffset + bits < 8)
    {
        uint8_t mask = ((1 << bits) - 1) << bitOffset;
        m_target[byteOffset] &= ~mask;
        m_target[byteOffset] |= value << bitOffset;
    }
    else
    {
        auto const leadingBits = (8 - bitOffset) & 0b111;
        if (leadingBits > 0)
        {
            auto const leadingMask = static_cast<stream_base_type>((1 << bitOffset) - 1);
            m_target[byteOffset] = (m_target[byteOffset] & leadingMask)
                | static_cast<stream_base_type>(value << bitOffset);
            value = value >> leadingBits;
            byteOffset++;
        }

        auto const fullBytes = (bits - leadingBits) >> 3;
        for (auto i = 0U; i < fullBytes; ++i)
        {
            m_target[byteOffset++] = static_cast<stream_base_type>(value);
            value = value >> 8;
        }

        auto const trailingBits = bits - leadingBits - 8 * fullBytes;
        if (trailingBits > 0)
        {
            auto const trailingMask = static_cast<stream_base_type>(~((1 << trailingBits) - 1));
            m_target[byteOffset] =
                (m_target[byteOffset] & trailingMask) | static_cast<stream_base_type>(value);
        }
    }
    m_offset += bits;
}

void MemoryBitStreamWriter::align(size_type alignment)
{
    auto const newOffset = alignAt(m_offset, alignment);
    write(0, newOffset - m_offset);
}

void ManagedBitStreamWriter::write(value_type value, size_type bits)
{
    m_sizeInBytes = inFullBytes(m_sizeInBits + bits);
    m_data.resize(m_sizeInBytes, 0);

    // always set pointer: might have changed because of resizing!
    m_writer.setTarget(m_data.data());
    m_writer.setBitOffset(m_sizeInBits);
    m_writer.write(value, bits);
    
    m_sizeInBits += bits;
}

void ManagedBitStreamWriter::align(size_type alignment)
{
    auto const newOffset = alignAt(m_sizeInBits, alignment);
    write(0, newOffset - m_sizeInBits);
}

auto ManagedBitStreamWriter::data() const -> const stream_base_type*
{
    return m_data.data();
}

auto ManagedBitStreamWriter::size() const -> size_type
{
    return m_data.size();
}

auto ManagedBitStreamWriter::sizeInBits() const -> size_type
{
    return m_sizeInBits;
}

auto ManagedBitStreamWriter::asVector() const -> std::vector<stream_base_type>
{
    return m_data;
}

}