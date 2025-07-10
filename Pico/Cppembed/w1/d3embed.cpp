#include <cstdio>               // for printf
#include <cstdint>              // for uint16_t
#include "pico/stdlib.h"       // core Pico functionality
#include "hardware/gpio.h"     // GPIO API
#include "hardware/adc.h"      // ADC API
#include "hardware/watchdog.h" // Watchdog API
#include "hardware/pwm.h"      // PWM API
#include "hardware/dma.h"      // DMA API
#include "hardware/i2c.h"      // I2C API
#include "hardware/spi.h"      // SPI API

int main(){
    /* Initialize SPI Instance on Pico */
    spi_init(spi0, 1000000); // Initialize SPI0 with a baud rate of 1 MHz
    gpio_set_function(2, GPIO_FUNC_SPI); // Set GPIO 2 as SPI0 SCK
    gpio_set_function(3, GPIO_FUNC_SPI); // Set GPIO 3 as SPI0 MOSI
    gpio_set_function(4, GPIO_FUNC_SPI); // Set GPIO 4 as SPI0 MISO

    /* I2C on Pico */
    i2c_init(i2c0, 100000); // Initialize I2C0 with a baud rate of 100 kHz
    gpio_set_function(0, GPIO_FUNC_I2C); // Set GPIO 0 as I2C0 SDA
    gpio_set_function(1, GPIO_FUNC_I2C); // Set GPIO 1 as I2C0 SCL
    gpio_pull_up(0); // Enable pull-up on SDA
    gpio_pull_up(1); // Enable pull-up on SCL

    /* DMA on Pico*/
    int dma_chan = dma_claim_unused_channel(true); // Claim an unused DMA channel and get its number
    dma_channel_config c = dma_channel_get_default_config(dma_chan); // Get default DMA channel config
    // Example: configure the channel (replace src/dst with actual addresses and size)
    // dma_channel_configure(dma_chan, &c, dst, src, transfer_count, false);
    // To start the DMA, you would typically enable it after configuration
    // dma_channel_start(dma_chan);
}