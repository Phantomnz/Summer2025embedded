#include <pico/stdlib.h>
#include "hardware/adc.h" 
#include "hardware/i2c.h"
#include <stdint.h> // for uint32_t
#include <stdio.h> // for printf
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "hardware/pwm.h"
#include "hardware/dma.h"
#include "hardware/watchdog.h"
#include "hardware/irq.h"
#include "pico/time.h"

// Deep sleep and wake up: Use the RP2040’s dormant mode via a hardware watchdog or external pin to enter ultra-low-power sleep, then wake on a reset or pin event.

/*
Error Reporting with LEDs
Flash an LED in a pattern to indicate fault codes (e.g., three blinks = sensor error). This lightweight method avoids requiring a serial console in headless embedded projects
*/

// Bootloader DFU modes: Holding BOOTSEL at reset enters USB mass-storage mode, allowing firmware updates via drag-and-drop, no special code needed. This is useful for embedded projects that need to be updated without a dedicated programmer.

int main(){
    watchdog_enable(1000, 1); // Enable watchdog with a timeout of 1000 ms
    stdio_init_all(); // Initialize all standard I/O
    wake_up_from_sleep(); // Custom function to wake up from sleep, if defined

    // DMA transfer example
    dma_channel_config dma_config = dma_channel_get_default_config(0); // Get default DMA channel configuration
    dma_channel_config_set_read_increment(&dma_config, true); // Enable read increment
    dma_channel_config_set_write_increment(&dma_config, false); // Disable write increment
    dma_channel_config_set_dreq(&dma_config, DREQ_SPI_TX); // Set DREQ for SPI transmit
    dma_channel_config_set_transfer_data_size(&dma_config, DMA_SIZE_32); // Set transfer data size to 32 bits

    //software timers
    add_repeating_timer_ms(1000, timer_callback, NULL, NULL); // Add a repeating timer that calls timer_callback every 1000 ms
}