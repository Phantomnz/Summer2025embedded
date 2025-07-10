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

// Shared ADC Calibration on Pico
// Read a known reference voltage several times, average the results, then subtract the offset from future readings to improve accuracy

// DMA Chaining on Pico
// You can link multiple DMA channels so that when one transfer completes it triggers the next-- ideal for complex, CPU-free data pipelines

int main() {
    stdio_init_all(); // Initialize all standard I/O

    // SPI Full-Duplex Transfers on Pico
    spi_init(spi0, 2*1000*1000); // Initialize SPI with a baud rate of 2 MHz
    // Map pins: SCK=2, MOSI=3, MISO=4
    gpio_set_function(2, GPIO_FUNC_SPI); // Set GPIO 2 as SPI SCK
    gpio_set_function(3, GPIO_FUNC_SPI); // Set GPIO 3 as SPI MOSI
    gpio_set_function(4, GPIO_FUNC_SPI); // Set GPIO 4 as SPI MISO
    // Send 0x9F command and read 2 bytes
    uint8_t cmd = 0x9F, rx[2]; 
    spi_write_read_blocking(spi0, &cmd, rx, 2); // Write command and read response
}