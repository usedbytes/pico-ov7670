cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(test_project C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(ov7670 main.c)

pico_enable_stdio_usb(ov7670 1)

pico_add_extra_outputs(ov7670)

target_link_libraries(ov7670 pico_stdlib hardware_i2c)
