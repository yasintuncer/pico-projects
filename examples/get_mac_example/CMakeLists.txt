add_executable(get_mac_address get_mac_address.c)

## set spi enabled
pico_enable_stdio_usb(get_mac_address 1)
pico_enable_stdio_uart(get_mac_address 0)

target_link_libraries(get_mac_address
    pico_stdlib
    pico_cyw43_arch_none    
)

pico_add_extra_outputs(get_mac_address)


