cmake_minimum_required(VERSION 3.10)
project(bittools VERSION 1.0 LANGUAGES CXX)

set(CMAKE_DEBUG_POSTFIX d)
set(BITTOOLS_CMAKE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH ${BITTOOLS_CMAKE_PATH})

include(TargetWarnings)

enable_testing()
add_subdirectory(src)
add_subdirectory(test)