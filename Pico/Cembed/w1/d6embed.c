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

bool repeating_callback(struct repeating_timer *t) {  // Callback function for the repeating timer
    static uint32_t count = 0; // Static variable to keep track of the number of times the callback has been called
    count++; // Increment the count each time the callback is called
    printf("Repeating callback called %u times\n", count);
    return true; // Return true to keep the timer running
}

void setup(){
    static struct repeating_timer timer; // Declare a static repeating timer
    add_repeating_timer_ms(200, &repeating_callback, NULL, &timer); // Add a repeating timer that calls the callback every 200 milliseconds
}

/*
Pico's PIO (programmable Input/Output):
- Allows you to offload simple I/O tasks into a tiny state machine
- Can generate custom serial protocols, waveforms, or even handle precise timing without CPU intervention
- Example: Using PIO to generate a PWM signal or to read a sensor with a custom protocol
- PIO programs are written in a simple assembly-like language and can be loaded into the PIO state machines
- PIO can be used for tasks like driving LEDs, reading sensors, or communicating with peripherals
*/

int main() {
    stdio_init_all(); // Initialize all standard I/O
    setup(); // Call the setup function to initialize the repeating timer

    while (true) {
        watchdog_update(); // Update the watchdog timer to prevent a reset
        sleep_ms(1000); // Sleep for 1 second
    }
    
    // Shared Flash Filesystem (LittleFS):
    int lfs; // Declare a variable for the LittleFS filesystem
    lfs_config cfg; // Declare a configuration structure for LittleFS
    littlefs_mount(&lfs, &cfg); // Mount the LittleFS filesystem
    FILE *f = fopen("file.txt", "w"); // Open a file for writing
    fprintf(f, "Hello, FS!\n"); // Write to the file
    fclose(f); // Close the file
    return 0; // Return 0 (not reached in this case)
}