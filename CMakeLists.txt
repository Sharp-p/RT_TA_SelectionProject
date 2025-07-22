cmake_minimum_required(VERSION 3.31)

# imports Pico SDK imports
include(pico_sdk_import.cmake)

project(SelectionProject)

# initialize Pico SDK
pico_sdk_init()

set(CMAKE_CXX_STANDARD 20)

# which file to compile
add_executable(SelectionProject main.cpp
        shell.hpp)

# for which target needs to create extra output files
pico_add_extra_outputs(SelectionProject)
# enable stdio for the ubs
pico_enable_stdio_usb(SelectionProject ENABLED)
# link the needed libraries
target_link_libraries(SelectionProject pico_stdlib)
# defines the configuration parameters
target_compile_definitions(SelectionProject PRIVATE PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS=-1)