cmake_minimum_required(VERSION 3.10)

get_filename_component(bin ${CMAKE_CURRENT_SOURCE_DIR} NAME_WE)
file(GLOB_RECURSE srcs  "*.cpp" "*.h" "*.qrc" "*.ui")
add_executable(${bin}  ${srcs})
target_link_libraries(${bin} jkqtplotter)
