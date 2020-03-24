cmake_minimum_required(VERSION 3.10)
project(JKQTPlotter LANGUAGES CXX VERSION 2019.06)

include("extern/cmake/common.cmake")


init_build()
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_subdirectory(lib)
get_directory_property(hasParent PARENT_DIRECTORY)
if(NOT hasParent)
option(BUILD_EXAMPLES "Build examples" OFF)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
endif()

option(BUILD_INCLUDE_XITS_FONTS "Include XITS fonts as resources in library" ON)

if(BUILD_INCLUDE_XITS_FONTS)
    target_compile_definitions(jkqtplotter INTERFACE -DAUTOLOAD_XITS_FONTS)
    target_compile_definitions(jkqtplotter INTERFACE -DUSE_XITS_FONTS )

    else()
        target_compile_definitions(jkqtplotter INTERFACE -DNO_XITS_FONTS  )
        # really should remove this duplicate flag negation
endif()



# to use this project
# add_subdirectory(path/jkqtplotter)
# add_executable(name ${sources})
# target_link_libraries(name jkqtplotter)
