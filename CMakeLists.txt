cmake_minimum_required(VERSION 3.10)
project(JKQTPlotter LANGUAGES CXX VERSION 2019.06)

include("extern/cmake/common.cmake")


init_build()

option(BUILD_INCLUDE_XITS_FONTS "Include XITS fonts as resources in library" ON)

if(BUILD_INCLUDE_XITS_FONTS)
        add_definitions(-DAUTOLOAD_XITS_FONTS)
        add_definitions(-DUSE_XITS_FONTS )
    else()
        add_definitions(-DNO_XITS_FONTS )
endif()

add_subdirectory(lib)



option(BUILD_JKQT_EXAMPLES "Build JKQT examples" OFF)
if(BUILD_JKQT_EXAMPLES)
    add_subdirectory(examples)
endif()



