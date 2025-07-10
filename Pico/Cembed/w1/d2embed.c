#include <pico/stdlib.h>
#include "hardware/adc.h" 
#include "hardware/i2c.h"
#include <stdint.h>
#include <stdio.h> // for printf
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "hardware/pwm.h"

int main() {
    stdio_init_all();
    printf("Hello, Pico!\n"); // printf sends a message over the USB serial port

    // ADC Initialization
    adc_init(); // Initialize the ADC hardware
    adc_gpio_init(26);// Initialize GPIO 26 for ADC input
    adc_select_input(0);// Select ADC input 0 (GPIO 26)
    uint16_t val = adc_read(); // Read the ADC value from the selected input
    printf("ADC Value: %u\n", val);// Print the ADC value to the console

    // I2C Initialization and Communication
    uint8_t addr = 0x50; // Example I2C address
    uint8_t txbuf[2] = {0x00, 0xFF}; // Example data buffer
    size_t len = 2; // Example length

    i2c_init(i2c0, 100 * 1000); // Initialize I2C with a baud rate of 100 kHz
    gpio_set_function(4, GPIO_FUNC_I2C); // Set GPIO 4 to I2C function (SDA)
    gpio_set_function(5, GPIO_FUNC_I2C); // Set GPIO 5 to I2C function (SCL)
    i2c_write_blocking(i2c0, addr, txbuf, len, false); // Write data to the I2C device

    // SPI Initialization and master mode
    spi_init(spi0, 1000 * 1000); // Initialize SPI with a baud rate of 1 MHz
    gpio_set_function(2, GPIO_FUNC_SPI); // set GPIO 2 to SPI function (SCK)
    gpio_set_function(3, GPIO_FUNC_SPI); // set GPIO 3 to SPI function (MOSI)
    spi_write_blocking(spi0, txbuf, len); // Write data to the SPI device

    // PWM Initialization and LED control
    gpio_set_function(20, GPIO_FUNC_PWM); // Set GPIO 20 to PWM function
    uint8_t slice = pwm_gpio_to_slice_num(20); // Get the PWM slice number for GPIO 20
    pwm_set_wrap(slice, 1000); // Set the PWM wrap value (e.g., 1000 for 1 kHz frequency)
    pwm_set_chan_level(slice, PWM_CHAN_A, 500); // Set the PWM level for channel A (50% duty cycle)
    pwm_set_enabled(slice, true); // Enable the PWM output

    return 0;
}