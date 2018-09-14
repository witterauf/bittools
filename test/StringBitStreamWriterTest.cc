#include <bittools/StringBitStreamWriter.h>
#include "catch.hpp"

using namespace bittools;

SCENARIO("Writing values", "[StringBitStreamWriter]")
{
    StringBitStreamWriter writer;

    GIVEN("A binary value is written")
    {
        writer.write(0b1100, 5);
        writer.write(0b1100, 5);

        THEN("The value is appended to the target string")
        {
            REQUIRE(writer.target() == "0011000110");
        }
    }
}