cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(lcd_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()


include_directories(lib/Config)
include_directories(lib/LCD)
include_directories(lib/GUI)
include_directories(lib/Fonts)
include_directories(lib/pico_base/include/)
include_directories(lib/pico_sync/include/)
include_directories(lib/generated/pico_base/)
include_directories(lib/pico_platform/include/)
include_directories(lib/hardware_regs/include/)
include_directories(lib/hardware_structs/include/)
include_directories(lib/pico_time/include/)
include_directories(lib/hardware_timer/include/)
include_directories(lib/hardware_base/include/)
include_directories(lib/hardware_sync/include/)
include_directories(lib/pico_stdio/include/)
include_directories(lib/hardware_gpio/include/)
include_directories(lib/hardware_uart/include/)
include_directories(lib/pico_stdlib/include/)
include_directories(lib/hardware_spi/include/)
include_directories(lib/hardware_pwm/include/)
include_directories(lib/hardware_i2c/include/)
include_directories(include/)


link_directories(lib/Config)
link_directories(lib/LCD)
link_directories(lib/GUI)
link_directories(lib/Fonts)
link_directories(lib/pico_base/include/)
link_directories(lib/pico_sync/include/)
link_directories(lib/generated/pico_base/)
link_directories(lib/pico_platform/include/)
link_directories(lib/hardware_regs/include/)
link_directories(lib/hardware_structs/include/)
link_directories(lib/pico_time/include/)
link_directories(lib/hardware_timer/include/)
link_directories(lib/hardware_base/include/)
link_directories(lib/hardware_sync/include/)
link_directories(lib/pico_stdio/include/)
link_directories(lib/hardware_gpio/include/)
link_directories(lib/hardware_uart/include/)
link_directories(lib/pico_stdlib/include/)
link_directories(lib/hardware_spi/include/)
link_directories(lib/hardware_pwm/include/)
link_directories(lib/hardware_i2c/include/)
link_directories(include/)

add_subdirectory(lib/Config)
add_subdirectory(lib/LCD)
add_subdirectory(lib/GUI)
add_subdirectory(lib/Fonts)
add_subdirectory(lib/pico_base)
add_subdirectory(lib/pico_sync)
add_subdirectory(lib/pico_platform)
add_subdirectory(lib/pico_time)
add_subdirectory(lib/hardware_timer)
add_subdirectory(lib/hardware_sync)
add_subdirectory(lib/pico_stdio)
add_subdirectory(lib/hardware_gpio)
add_subdirectory(lib/hardware_uart)
add_subdirectory(lib/pico_stdlib)
add_subdirectory(lib/hardware_spi)
add_subdirectory(lib/hardware_pwm)
add_subdirectory(lib/hardware_i2c)

add_executable(output
    lcd_main.c
    character_config.c
    displaystate.c
    inputs.c
    inventory.c
    itemlist.c
    menus.c
    player_character.c

)

pico_enable_stdio_usb(output 1)
pico_enable_stdio_uart(output 0)

pico_add_extra_outputs(output)

target_link_libraries(output
                pico_stdlib
                Fonts
                LCD
                GUI
                Config
                hardware_spi
                hardware_i2c
                hardware_pwm
                pico_multicore
                pico_sync
)

