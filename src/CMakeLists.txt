cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(lcd_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_subdirectory(lib/Config)
add_subdirectory(lib/LCD)
add_subdirectory(lib/GUI)
add_subdirectory(lib/Fonts)

include_directories(lib/Config)
include_directories(lib/LCD)
include_directories(lib/GUI)
include_directories(lib/Fonts)


add_executable(output
    lcd_main.c
)

pico_enable_stdio_usb(output 1)
pico_enable_stdio_uart(output 1)

pico_add_extra_outputs(output)

target_link_libraries(output pico_stdlib Fonts LCD GUI Config hardware_spi hardware_i2c hardware_pwm)