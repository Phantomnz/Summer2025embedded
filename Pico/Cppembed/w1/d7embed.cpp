#include <cstdio>               // for printf
#include <cstdint>              // for uint16_t
#include "pico/stdlib.h"       // core Pico functionality
#include "hardware/gpio.h"     // GPIO API
#include "hardware/adc.h"      // ADC API
#include "hardware/watchdog.h" // Watchdog API
#include "hardware/multicore.h" // Multicore API

int main() {
    // GPIO Pull-up/Pull-down Example:  Configure internal pull resistors to define default pin state
    stdio_init_all(); // Initialize all standard I/O
    gpio_init(15); // Initialize GPIO pin 15
    gpio_set_pulls(15, false, true); // Disable pull-up and enable pull-down resistors

    // Pico Multicore FIFO messaging Messaging Example: Send messages between cores using the built-in FIFO
    multicore_launch_core1(core1_entry); // Launch core 1 with the function core1_entry
    multicore_fifo_push_blocking(0xDEADBEEF); // Push a message to the FIFO
    uint32_t msg = multicore_fifo_pop_blocking(); // Pop a message from the FIFO
}