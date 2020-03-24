cmake_minimum_required(VERSION 3.10)

find_package( OpenCV 4)
if(OpenCV_FOUND)
    get_filename_component(bin ${CMAKE_CURRENT_SOURCE_DIR} NAME_WE)
    file(GLOB_RECURSE srcs  "*.cpp" "*.h" "*.qrc" "*.ui")
    add_executable(${bin} ${bin}.cpp ${srcs})
    target_link_libraries(${bin} PUBLIC jkqtplotter)
    print_list(${OpenCV_INCLUDE_DIRS} "")
    # opencv
    message("${bin}")
    target_include_directories(${bin} PUBLIC ${OpenCV_INCLUDE_DIRS} )
    target_link_libraries(${bin} PUBLIC ${OpenCV_LIBS} )

endif(OpenCV_FOUND)
