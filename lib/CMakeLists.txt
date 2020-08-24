cmake_minimum_required(VERSION 3.10)
# changes means you need to rerun cmake to update

file(GLOB_RECURSE utils-srcs  "*.cpp" "*.h" "*.qrc")
#print_list("jkqtplotter: " utils-srcs)

#qt5
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
#message("Needs qt5 and svg\n sudo apt install qt5-defaults libqt5svg5-dev " )
find_package(Qt5 5.9 REQUIRED Core Gui Widgets PrintSupport Svg Xml OpenGL)

add_library(jkqtplotter ${utils-srcs} ${utils-headers}) # must be after the qt stuff is set!

target_compile_features(jkqtplotter PUBLIC cxx_std_17)
#target_configure_warnings(jkqtplotter)
# We need this directory, and users of our library will need it too
target_include_directories(jkqtplotter SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(jkqtplotter SYSTEM PUBLIC ${Qt5Widgets_INCLUDE_DIRS}) # automatic with the Qt5::Core etc
target_link_libraries(jkqtplotter PUBLIC Qt5::Core Qt5::Gui Qt5::Widgets Qt5::PrintSupport Qt5::Svg Qt5::Xml Qt5::OpenGL)

target_compile_definitions(jkqtplotter INTERFACE -DAUTOLOAD_XITS_FONTS)
target_compile_definitions(jkqtplotter INTERFACE -DUSE_XITS_FONTS )


# needs
# sudo apt install libqt5svg5-dev
