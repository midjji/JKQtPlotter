cmake_minimum_required(VERSION 3.10)
project(simpletest LANGUAGES CXX)


# include JKQTPlotter

#find_package(jkqtplotter REQUIRED) # provides jkqtplotter

# add the example executable 
add_executable(simpletest0 simpletest.cpp)
target_link_libraries(simpletest0 jkqtplotter)
