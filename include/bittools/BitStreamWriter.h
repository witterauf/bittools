#pragma once

#include <cstdint>
#include <cstddef> // size_t
#include <vector>

namespace bittools {

class BitStreamWriter
{
public:
    using size_type = size_t;
    using value_type = uint64_t;
    using stream_base_type = uint8_t;

    virtual void write(value_type value, size_type bits) = 0;
    virtual void writeBuffer(const uint8_t* data, size_t bits);
    virtual auto bitOffset() const -> size_type = 0;
    virtual void align(size_type alignment) = 0;
};

class MemoryBitStreamWriter : public BitStreamWriter
{
public:
    MemoryBitStreamWriter() = default;

	/// Constructs a BitStreamWriter from a memory target.
	/// @param target a pointer to the memory to write to
	/// @param start_offset an offset, in bits, that is added to target
    explicit MemoryBitStreamWriter(stream_base_type* target, size_type startOffset);

	/// Writes a value of length bits into memory.
	/// @param value value to write
	/// @param bits length in bits
	void write(value_type value, size_type bits) override;

    void align(size_type alignment) override;

	/// Get the current offset relative to target.
    virtual auto bitOffset() const -> size_type override;
	/// Set the current offset, in bits.
    void setBitOffset(size_type offset);
	/// Set a new target.
    void setTarget(stream_base_type* target);

private:
	/// Target to write bit strings to.
	stream_base_type* m_target = nullptr;
	/// Offset, in bits, that is added to target.
	size_type m_offset = 0;
};

/// A wrapper for BitStreamWriter that performs automatic memory management.
class ManagedBitStreamWriter : public BitStreamWriter
{
public:
    using size_type = BitStreamWriter::size_type;

    void write(value_type value, size_type bits) override;
    auto bitOffset() const -> size_type override { return m_sizeInBits; }
    void align(size_type alignment) override;

    /// Returns a pointer to the data produced and the number of bits written
    auto data() const -> const stream_base_type*;
    auto size() const -> size_type;
    auto sizeInBits() const -> size_type;
    auto asVector() const -> std::vector<stream_base_type>;

private:
    std::vector<stream_base_type> m_data;
    MemoryBitStreamWriter m_writer;
    size_type m_sizeInBytes = 0;
    size_type m_sizeInBits = 0;
};

}