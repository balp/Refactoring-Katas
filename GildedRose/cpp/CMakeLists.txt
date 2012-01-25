# CMakefile for building the kata file with the Google Testing Framework
#
#

cmake_minimum_required (VERSION 2.8 )
project ( GildedRose )
ENABLE_TESTING()

include_directories( gtest/include ${CMAKE_CURRENT_SOURCE_DIR} )
add_subdirectory( gtest )

add_executable ( GildedRoseTest
	${GTEST}
	GildedRose.h
	GildedRose.cc
	GildedRoseTest.cc
)

target_link_libraries( GildedRoseTest gtest_main )

add_test( NAME gtest_gildedrose
	COMMAND "$<TARGET_FILE:GildedRoseTest>"
)
