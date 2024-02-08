PROJECT(sample_wifi_chip_info)

include_directories(/pico-sdk/lib/cyw43-driver/include)
include_directories(/pico-sdk/lib/cyw43-driver/src)
add_definitions()


add_executable(sample_wifi_chip_info /pico-sdk/lib/cyw43-driver/src/cyw43_ll.c chip_info.c )

target_link_libraries(sample_flash
    pico_stdlib 
    
)


