cmake_minimum_required(VERSION 3.10)
project(JKQTPlotter LANGUAGES CXX VERSION 2019.06)

include("extern/cmake/common.cmake")


init_build()

add_subdirectory(lib)
option(BUILD_EXAMPLES "Build examples" ON)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# nothing else is really an option, the default is always right ...
# shared vs static libs shouldnt be manually set in a million places...
# opencv should be checked for, but does not compile anyways...


option(BUILD_INCLUDE_XITS_FONTS "Include XITS fonts as resources in library" ON)

if(BUILD_INCLUDE_XITS_FONTS)
        add_definitions(-DAUTOLOAD_XITS_FONTS)
        add_definitions(-DUSE_XITS_FONTS )
    else()
        add_definitions(-DNO_XITS_FONTS )
endif()
