# CMakefile for building the kata file with the Google Testing Framework
#
#

cmake_minimum_required (VERSION 2.8 )
project ( GildedRose )
ENABLE_TESTING()

set(CMAKE_CXX_FLAGS "-std=c++0x")

include_directories( gtest/include ${CMAKE_CURRENT_SOURCE_DIR} )
add_subdirectory( gtest )

add_executable ( GildedRoseTest
	${GTEST}
	GildedRose.h
	GildedRose.cc
	GildedRoseTest.cc
)

target_link_libraries( GildedRoseTest gtest_main )

add_executable(GildedRoseTextTests
	GildedRose.h
	GildedRose.cc
	GildedRoseTextTests.cc
)

add_executable(GildedRose
	GildedRoseUnitTests.cc
	GildedRose.cc
)

target_link_libraries( GildedRose gtest_main )

add_test( NAME gtest_gildedrose
	COMMAND "$<TARGET_FILE:GildedRoseTest>"
)

add_test( NAME gtest_gildedrose2
	COMMAND "$<TARGET_FILE:GildedRose>"
)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
            ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
            ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen" VERBATIM
            )
endif(DOXYGEN_FOUND)
