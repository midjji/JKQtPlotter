cmake_minimum_required(VERSION 3.10)

get_filename_component(bin ${CMAKE_CURRENT_SOURCE_DIR} NAME_WE)
file(GLOB_RECURSE srcs  "*.cpp" "*.h" "*.qrc" "*.ui")
add_executable(${bin} stepplots.cpp)
target_link_libraries(${bin} jkqtplotter)
add_executable(${bin}_vertical stepplots_vertical.cpp)
target_link_libraries(${bin}_vertical jkqtplotter)

