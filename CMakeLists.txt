cmake_minimum_required(VERSION 3.31)

# imports Pico SDK imports
include(pico_sdk_import.cmake)

project(SelectionProject)

# initialize Pico SDK
pico_sdk_init()

set(CMAKE_CXX_STANDARD 20)

add_executable(SelectionProject main.cpp)