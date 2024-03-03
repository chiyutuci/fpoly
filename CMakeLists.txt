cmake_minimum_required(VERSION 3.25)
project(ffpoly)

set(CMAKE_CXX_STANDARD 20)

add_executable(ffpoly main.cpp ffpoly.h ffpoly.h)

# flint library
find_library(FLINT_LIBRARY NAMES flint)
if (NOT FLINT_LIBRARY)
    message(FATAL_ERROR "flint library not found")
endif ()
target_link_libraries(ffpoly ${FLINT_LIBRARY})