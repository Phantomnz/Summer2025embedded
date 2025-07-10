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
#include "pico/flash.h"
#include "pico/multicore.h"

// Dual Core processing 
int j = 0;
int i = 0;
int k = 0;
void core1_entry() {
    while(i < 10) {
        printf("Core 1 is running\n");
        i++;
        // Simulate some work by sleeping
        sleep_ms(1000); // Sleep for 1 second
    }
}

// Shared timer between cores
void alarm_callback() {
    printf("Time fired on core %d\n", get_core_num());
}

int main(){
    // Initialize the standard I/O
    stdio_init_all();
    // Initialize the first core
    multicore_launch_core1(core1_entry);
    // Main loop for core 0
    while(j < 10){
        printf("Core 0 is running\n");
        j++;
        sleep_ms(1000); // Sleep for 1 second
    }

    add_alarm_in_ms(1000, alarm_callback, NULL, true); // Set an alarm to call the callback every second
    while (k < 10) {
        // Keep the main loop running to allow alarms to fire
        k++;
        tight_loop_contents(); // This is a placeholder for doing other work
    }

    // Pico PIO-driven PWM: Use a PIO state machine to generate PWM on any pin with precise timing
    // PIO program to toggle pin x at duty cycle d:
    { .instructions = {
        pio_encode_set(pio_pins, 1), // Set pin high
        pio_encode_wait(pio_pins, 0), // Wait for pin to be low
        },
    .length = 2, // Length of the program in instructions
    };
    // Load, configure, and start the PIO state machine
    pio_sm_init(pio0, sm, offset, &cfg);

    return 0;
}