cmake_minimum_required(VERSION 3.0)
if (BUILD_HAS_OPENCV)
    find_package( OpenCV  )
    if(OpenCV_FOUND)

        set(EXAMPLE_NAME rgbimageplot_opencv)
        set(EXENAME jkqtptest_${EXAMPLE_NAME})

        message( STATUS "..   Building Example ${EXAMPLE_NAME}" )

        # Set up source files
        set(SOURCES ${EXAMPLE_NAME}.cpp)
        set(HEADERS )
        set(RESOURCES  )
        set(UIS  )

        add_executable(${EXENAME} WIN32 ${SOURCES} ${HEADERS} ${RESOURCES} ${UIS})
        target_include_directories(${EXENAME} PRIVATE ../../lib)
        if(BUILD_STATIC_LIBS)
            target_link_libraries(${EXENAME} JKQTPlotterLib)
        elseif(BUILD_SHARED_LIBS)
            target_link_libraries(${EXENAME} JKQTPlotterSharedLib)
        endif()
        include_directories( ${OpenCV_INCLUDE_DIRS} )
        target_link_libraries(${EXENAME} ${OpenCV_LIBS} )


        # Installation
        if(LIB_INSTALL)
            install(TARGETS ${EXENAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
        endif(LIB_INSTALL)
    endif(OpenCV_FOUND)
endif(BUILD_HAS_OPENCV)