cmake_minimum_required(VERSION 3.10)

get_filename_component(bin ${CMAKE_CURRENT_SOURCE_DIR} NAME_WE)

set(SOURCES jkqtplot_test.cpp testmain.cpp TestWidgetBarcharts.cpp TestWidgetContourPlots.cpp TestWidgetEmptyPlot.cpp TestWidgetFunctionPlots.cpp TestWidgetGeometry.cpp TestWidgetGraphs.cpp TestWidgetImages.cpp TestWidgetLogGraphs.cpp TestWidgetParamScatterPlots.cpp TestWidgetPeaksPlots.cpp TestWidgetRGBImages.cpp )
set(HEADERS testmain.h TestWidgetBarcharts.h TestWidgetContourPlots.h TestWidgetEmptyPlot.h TestWidgetFunctionPlots.h TestWidgetGeometry.h TestWidgetGraphs.h TestWidgetImages.h TestWidgetLogGraphs.h TestWidgetParamScatterPlots.h TestWidgetPeaksPlots.h TestWidgetRGBImages.h)

add_executable(${bin} ${bin}.cpp ${SOURCES} ${HEADERS} jkqtplot_test.qrc)
target_link_libraries(${bin} jkqtplotter)


