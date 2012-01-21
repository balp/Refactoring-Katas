# CMakefile for building the kata file with the Google Testing Framework
#
#

cmake_minimum_required (VERSION 2.8 )
project ( GildedRose )
ENABLE_TESTING()

include_directories( gtest/include )
add_subdirectory( gtest )

add_executable ( GildedRose
	${GTEST}
	GildedRose.cc
)

target_link_libraries( GildedRose gtest_main )

add_test( NAME gtest_gildedrose
	COMMAND "$<TARGET_FILE:GildedRose>"
)
