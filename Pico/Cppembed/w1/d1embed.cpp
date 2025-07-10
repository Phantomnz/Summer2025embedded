#include <cstdio>               // for printf
#include <cstdint>              // for uint16_t
#include "pico/stdlib.h"       // core Pico functionality
#include "hardware/gpio.h"     // GPIO API
#include "hardware/adc.h"      // ADC API

// ESP32 Toolchain with idf.py - ESP32 Projects are built using the ESP-IDF framework.
// This wrapper helps configure, build, flash, and monitor ESP32 projects.

// To configure a pin on the Raspberry Pi Pico, you can use the following code snippet:
//   gpio_init(25);
//   gpio_set_dir(25, GPIO_OUT);
//   gpio_put(25, 1);

// ADC reading on Raspberry Pi Pico - example to read an analog pin:
//   adc_init();
//   adc_select_input(0);
//   uint16_t result = adc_read();

int main() {
    // 1) Initialize all stdio (sets up USB/UART for printf)
    stdio_init_all();

    // 2) Configure and blink the onboard LED (GPIO25)
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);
    gpio_put(25, 1);
    sleep_ms(500);
    gpio_put(25, 0);

    // 3) ADC example: read from ADC channel 0
    adc_init();
    adc_select_input(0);
    uint16_t result = adc_read();

    // 4) Print the ADC reading
    printf("ADC reading: %u\n", result);

    // 5) Keep the program alive
    while (true) {
        tight_loop_contents();
    }

    return 0;
}
