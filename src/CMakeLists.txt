cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(lcd_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_subdirectory(lib/Config)
add_subdirectory(lib/LCD)

include_directories(lib/Config)
include_directories(lib/LCD)


add_executable(test
    lcd_main.c
)

pico_enable_stdio_usb(test 1)
pico_enable_stdio_uart(test 1)

pico_add_extra_outputs(test)

target_link_libraries(test pico_stdlib LCD Config hardware_spi hardware_i2c hardware_pwm)