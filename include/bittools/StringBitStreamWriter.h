#pragma once

#include "BitStreamWriter.h"
#include <string>

namespace bittools {

class StringBitStreamWriter : public BitStreamWriter
{
public:
    void reset();
    void write(value_type value, size_type bits) override;
    auto bitOffset() const -> size_type override;

    auto target() const -> const std::string&;

private:
    std::string m_target;
};

}