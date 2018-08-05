#include "bittools/BitStreamWriter.h"
#include "catch.hpp"

using namespace bittools;

SCENARIO("MemoryBitStreamWriter", "[BitTools][MemoryBitStreamWriter]")
{
    uint8_t target[8] = { 0 };
    MemoryBitStreamWriter writer{ target, 0 };

    GIVEN("An initialized MemoryBitStreamWriter")
    {
        WHEN("A write does not cross the next byte boundary")
        {
            writer.write(0x1a, 5);

            THEN("Only those bits are written")
            {
                REQUIRE(target[0] == 0x1a);
            }
        }
        WHEN("A write crosses the next byte boundary")
        {
            writer.write(0x1aa, 9);

            THEN("One byte and the trailing bits are written")
            {
                REQUIRE(target[0] == 0xaa);
                REQUIRE(target[1] == 0x01);
            }
        }
        WHEN("A write crosses multiple byte boundaries")
        {
            writer.write(0x1aaaa, 17);

            THEN("One byte and the trailing bits are written")
            {
                REQUIRE(target[0] == 0xaa);
                REQUIRE(target[1] == 0xaa);
                REQUIRE(target[2] == 0x01);
            }
        }
    }
}
