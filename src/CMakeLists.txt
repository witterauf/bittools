set(BITTOOLS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../include/)

set(BITTOOLS_HEADERS
    ${BITTOOLS_INCLUDE_DIR}/bittools/Algorithms.h
    ${BITTOOLS_INCLUDE_DIR}/bittools/BitStreamWriter.h
    ${BITTOOLS_INCLUDE_DIR}/bittools/StringBitStreamWriter.h
    ${BITTOOLS_INCLUDE_DIR}/bittools/BitField.h
    ${BITTOOLS_INCLUDE_DIR}/bittools/BitMap.h
)

add_library(BitTools
    ${BITTOOLS_HEADERS}
    BitStreamWriter.cc
    StringBitStreamWriter.cc
)
target_include_directories(BitTools
    INTERFACE
         $<INSTALL_INTERFACE:include/>
         $<BUILD_INTERFACE:${BITTOOLS_INCLUDE_DIR}/>
    PRIVATE
        ${BITTOOLS_INCLUDE_DIR}/bittools
)
target_all_warnings(BitTools)
target_warnings_are_errors(BitTools)
target_compile_features(BitTools PUBLIC cxx_std_17)
add_library(BitTools::BitTools ALIAS BitTools)

##[ installation ]#############################################################

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    BitToolsConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)
configure_file(${BITTOOLS_CMAKE_PATH}/BitToolsConfig.cmake.in BitToolsConfig.cmake @ONLY)
    
install(TARGETS BitTools EXPORT BitTools
    ARCHIVE DESTINATION "lib/"
    LIBRARY DESTINATION "lib/"
    RUNTIME DESTINATION "bin/"
)
install(DIRECTORY ${BITTOOLS_INCLUDE_DIR} DESTINATION include)
install(EXPORT BitTools NAMESPACE BitTools:: DESTINATION lib/cmake/bittools)
install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/BitToolsConfigVersion.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/BitToolsConfig.cmake
    DESTINATION
        lib/cmake/bittools
)