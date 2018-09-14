set(CATCH_MAIN catch_main.cc)

add_executable(BitToolsTests
    BitStreamWriterTest.cc
    StringBitStreamWriterTest.cc
    ${CATCH_MAIN}
)
target_link_libraries(BitToolsTests BitTools)
add_test(BitToolsTests COMMAND BitToolsTests)
