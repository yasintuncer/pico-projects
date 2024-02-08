#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/flash.h"
#include "hardware/irq.h"
#include "hardware/sync.h"

#define FLASH_TARGET_OFFSET (256 * 1024) // 1MB offset
#define FLASH_PAGE_SIZE 256              // Define flash page size (adjust as needed)
#define FILL_CONTENT 0                   // Fill content for erasing flash

// Pointer to the location in flash where data will be stored
const uint8_t *FlashTargetContents = (const uint8_t *)(XIP_BASE + FLASH_TARGET_OFFSET);

// Function to prepare flash by erasing and filling with specified content
void prepare_flash(uint8_t fill) {
    // Disable interrupts during flash operations
    uint32_t ints = save_and_disable_interrupts();

    // Erase flash range
    flash_range_erase(FLASH_TARGET_OFFSET, FLASH_SECTOR_SIZE);

    // Prepare data to be written (fill with specified content)
    uint8_t erase_data[FLASH_PAGE_SIZE];
    for (int i = 0; i < FLASH_PAGE_SIZE; i++) {
        erase_data[i] = fill;
    }

    // Program flash with prepared data
    flash_range_program(FLASH_TARGET_OFFSET, erase_data, FLASH_PAGE_SIZE);

    // Restore interrupts
    restore_interrupts(ints);
}

int main() {
    // Initialize standard I/O
    stdio_init_all();

    // Wait for some time
    sleep_ms(5000);

    // Notify that flash preparation is starting
    printf("Preparing flash...\n");

    // Prepare flash with fill content
    prepare_flash(FILL_CONTENT);

    // Notify that flash preparation is done
    printf("Flash prepared.\n");

    // Wait for a short time
    sleep_ms(1500);

    // Main loop
    while (true) {
        // Generate random data to write to flash
        uint8_t data[FLASH_PAGE_SIZE];
        for (int i = 0; i < FLASH_PAGE_SIZE; i++) {
            data[i] = rand() % 256;
        }

        // Disable interrupts during flash write
        uint32_t ints = save_and_disable_interrupts();

        // Program flash with generated data
        flash_range_program(FLASH_TARGET_OFFSET, data, FLASH_PAGE_SIZE);

        // Restore interrupts
        restore_interrupts(ints);

        // Check if data was written correctly
        bool is_same = true;
        for (int i = 0; i < FLASH_PAGE_SIZE; i++) {
            if (FlashTargetContents[i] != data[i]) {
                is_same = false;
                printf("Data not the same at address %d\n", i);
                break;
            }
        }

        // Notify that flash write is done
        printf("Write to flash done.\n");

        // Wait for a short time
        sleep_ms(1500);
    }

    return 0;
}
