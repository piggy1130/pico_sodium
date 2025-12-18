cmake_minimum_required(VERSION 3.13)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(ttl_pulse C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(ttl_pulse
    ${CMAKE_CURRENT_LIST_DIR}/ttl_pulse.c
)

target_link_libraries(ttl_pulse
    pico_stdlib
    hardware_gpio
)

# Optional: enable printf over USB (handy for debugging)
pico_enable_stdio_usb(ttl_pulse 1)
pico_enable_stdio_uart(ttl_pulse 0)

# If you ever build for Pico W, this project doesn't need WiFi, so no cyw43 lib required.

pico_add_extra_outputs(ttl_pulse)
