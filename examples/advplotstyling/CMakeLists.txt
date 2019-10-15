cmake_minimum_required(VERSION 3.10)

get_filename_component(bin ${CMAKE_CURRENT_SOURCE_DIR} NAME_WE)
add_executable(${bin} ${bin}.cpp)
target_link_libraries(${bin} jkqtplotter)
