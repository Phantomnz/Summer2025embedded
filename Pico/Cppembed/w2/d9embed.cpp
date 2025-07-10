#include <cstdio>               // for printf
#include <cstdint>              // for uint16_t
#include "pico/stdlib.h"       // core Pico functionality
#include "hardware/gpio.h"     // GPIO API
#include "hardware/adc.h"      // ADC API
#include "hardware/watchdog.h" // Watchdog API
#include "hardware/multicore.h" // Multicore API
#include "pico/flash.h" // Flash API for persistent storage
#include "hardware/spi.h"      // SPI API

int main(){
    // SPI DMA Transfers: Use DMA to offload SPI for large data blocks
    // Claim a DMA channel
    int chan = dma_claim_unused_channel(true); // true for panic on failure
    dma_channel_config cfg  = dma_channel_get_default_config(chan); // Get default configuration for the channel
    channel_config_set_transfer_data_size(&cfg, DMA_SIZE_8); // Set data size to 8 bits
    channel_config_set_read_increment(&cfg, false); // Disable read increment
    channel_config_set_write_increment(&cfg, true); // Enable write increment
    dma_channel_configure(
        chan, &cfg,
        &tx_buffer, // write address (SPI TX FIFO)
        &rx_buffer, // read address (Your RX buffer)
        BUFFER_SIZE, // Number of bytes to transfer
        true // Start immediately
    );
    spi_init(spi0, 1000 * 1000); // Initialize SPI at 1 MHz
    gpio_set_function(2, GPIO_FUNC_SPI); // Set GPIO 2 as SPI0

    // Low-Power Dormant mode: Put the RP2040 into dormant mode until a specific GPIO interrupt
    gpio_set_irq_enabled_with_callback(
        WAKE_PIN, GPIO_IRQ_EDGE_RISE, true, &wake_callback // Set up GPIO interrupt on WAKE_PIN for rising edge
    );
    sleep_run_from_rosc(); // Switch to low-power clock source
    sleep_goto_dormant_until_pin_high(WAKE_PIN); // Enter dormant mode until WAKE_PIN goes high

    // Flash Wear Leveling with TinyUSB: Use TinyUSB's littlefs support to mount and manage filesystem wear
    const fs_mount_t mount = {
        .type = FS_LITTLEFS, // Use LittleFS
        .mnt_point = "/flash", // Mount point
        .format_if_mount_failed = true, // Format if mount fails
    };
    fs_mount(&mount); // Mount the filesystem
    FILE *f = fopen("/flash/config.txt", "w"); // Open a file for writing
    fprintf(f, "mode=1\n"); // Write configuration
    fclose(f); // Close the file
}