cmake_minimum_required(VERSION 3.10)
project(JKQTPlotter LANGUAGES CXX VERSION 2019.06)

include("extern/cmake/common.cmake")


init_build()

add_subdirectory(lib)
get_directory_property(hasParent PARENT_DIRECTORY)
# mark as advanced instead
if(NOT hasParent)
    option(BUILD_JKQT_EXAMPLES "Build examples" OFF)
    if(BUILD_JKQT_EXAMPLES)
        add_subdirectory(examples)
    endif()
endif()




