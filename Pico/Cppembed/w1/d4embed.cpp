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

#define LED_PIN 25 // GPIO pin for the onboard LED 
// #define is used for hardware aliasing, which is a common practice in embedded systems to improve code readability and maintainability.


/* Polling vs Interrupts: Polling checks a pin or peripheral repeatedly in a loop.
Interrupts allow the microcontroller to sleep or work on other tasks until an event occurs (like a button press), improving efficiency
*/
int main(){
    volatile uint32_t count = 0; // Volatile to prevent optimization issues with the count variable
    // volatile Keyword: Essential when working with hardware registers or variables modified in an ISR. It tells the compiler not to optimize access to that variable, ensuring real-time updates.
    stdio_init_all(); // Initialize all standard I/O, including UART for debugging
    gpio_init(LED_PIN); // Initialize the GPIO pin for the LED
    gpio_set_dir(LED_PIN, GPIO_OUT); // Set the LED pin as an output
    gpio_put(LED_PIN, 0); // Turn off the LED initially

    // PORT |= (1 << LED_PIN);  Set the LED pin as an output
    // PORT &= ~(1 << LED_PIN);  Turn off the LED initially , these are examples of bit manipulation in C, often used in embedded systems to control hardware directly.
    adc_init(); // Initialize the ADC (Analog-to-Digital Converter)
    adc_select_input(0); // Select ADC input channel 0 (GPIO 26 on the Pico)
    adc_read(); // Read the ADC value to ensure it's ready   
}