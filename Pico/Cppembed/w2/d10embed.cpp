#include <cstdio>               // for printf
#include <cstdint>              // for uint16_t
#include "pico/stdlib.h"       // core Pico functionality
#include "hardware/gpio.h"     // GPIO API
#include "hardware/adc.h"      // ADC API
#include "hardware/watchdog.h" // Watchdog API
#include "hardware/multicore.h" // Multicore API
#include "pico/flash.h" // Flash API for persistent storage
#include "hardware/spi.h"      // SPI API

// If your embedded project grows, list multiple source files in your CMakefile explicitly.

int main(){
    // Dual Core Lockstep: You can synchronize tasks on both RP2040 cores with multicore_fifo_push_blocking() and multicore_fifo_pop_blocking(). One core can wait on the other core to finish a task, or they can run in parallel.

    // Core 0
    multicore_fifo_push_blocking(0x12345678); // Push a value to the FIFO queue of core 1
    // Core 1
    uint32_t token = multicore_fifo_pop_blocking(); // Pop a value from the FIFO queue of core 0
    // Both cores proceed in lockstep once they exchange the token.

    // Brown-Out detection: Enable power brown-out detection to reset on low voltage
    bi_decl(bi_1pin_with_name(VBUS_PIN, "USB VBUS")); // Declare a pin for USB VBUS detection
    // IN CMakeLists: link pico_bootsel_via_double_reset to reset reliably
}
