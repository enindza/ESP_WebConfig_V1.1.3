cmake_minimum_required(VERSION 3.9)
project(BlinkPattern)

set(CMAKE_CXX_STANDARD 11)

add_executable(BlinkPattern main.cpp lib/BlinkPattern.cpp lib/BlinkPattern.h)

# add extra include directories
include_directories(/usr/local/include)


# add extra lib directories
link_directories(/usr/local/lib)

file(GLOB SOURCES
        *.h
        *.cpp
        )