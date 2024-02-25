PROJECT(sample_flash)
add_executable(sample_flash flash.c)

target_link_libraries(sample_flash
    pico_stdlib 
    hardware_flash
)
