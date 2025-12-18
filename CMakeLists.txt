cmake_minimum_required(VERSION 3.13)

# Pull in PICO SDK (must be before project)
include(pico_sdk_import.cmake)

project(ttl_pulse C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(ttl_pulse
    ttl_pulse.c
)

# We use stdlib + hardware_gpio + time (alarms)
target_link_libraries(ttl_pulse
    pico_stdlib
    hardware_gpio
)

# Optional: enable printf over USB serial (recommended for debugging)
pico_enable_stdio_usb(ttl_pulse 1)
pico_enable_stdio_uart(ttl_pulse 0)

pico_add_extra_outputs(ttl_pulse)
