#include <cstdio>               // for printf
#include <cstdint>              // for uint16_t
#include "pico/stdlib.h"       // core Pico functionality
#include "hardware/gpio.h"     // GPIO API
#include "hardware/adc.h"      // ADC API
#include "hardware/watchdog.h" // Watchdog API


#include "pico/multicore.h" // enables multicore functionality

int main(){
    multicore_launch_core1(core1_entry); // This code runs the function core1_entry on the second core of the RP2040
    stdio_init_all(); // Initialize all standard I/O

    // Pin direction setup
    gpio_set_dir(25, GPIO_OUT); // Set GPIO 25 as output (typically the onboard LED on RP2040 boards)
    gpio_set_dir(0, GPIO_IN); // Set GPIO 0 as input (can be used for a button or other input)
}

/*
Optimizing flash memory usage:
For embedded systems, reduce code size by using -0s with GCC to optimize for size.
This can be done by adding it to the CMakeLists.txt file:
add_compile_options(-Os)
This is useful for embedded systems where flash memory is limited, such as the RP2040.
*/