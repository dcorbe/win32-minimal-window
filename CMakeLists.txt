cmake_minimum_required(VERSION 3.26)
project(win32_minimal_window)

set(CMAKE_CXX_STANDARD 17)

add_executable(win32_minimal_window
        main.cpp
        window.cpp
        window.h)
