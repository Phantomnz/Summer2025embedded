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

int main(){
    // Interrupt configuration
    stdio_init_all(); // Initialize standard I/O for debugging
    gpio_set_irq_enabled_with_callback(2, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, NULL); // Set up GPIO 2 for IRQ on rising and falling edges
    delay_ms(1000); // Wait for 1 second to ensure everything is set up
    gpio_check(2); // Check the state of GPIO 2
    delay_ms(50); // Wait for 50 milliseconds to debounce
    gpio_check(2); // Check the state of GPIO 2 again

    // Real-time operating system (RTOS) Task configuration
    // Note: The Pico SDK does not have built-in RTOS support, but you can use FreeRTOS or similar libraries for task management.
    // For example, you can create a task that runs periodically:
    // xTaskCreate(task_function, "TaskName", stack_size, NULL, priority, &task_handle);
    // Example task function (to be defined):
    // void task_function(void *pvParameters) {
    //     while (1) {
    //         // Task code here
    //     }
    // }
    // or use a simpler scheduler by polling flags set in ISRs

    uint32_t status = save_and_disable_interrupts(); // Save and disable interrupts
    shared_var = 42; // Set a shared variable
    restore_interrupts(status); // Restore interrupts

    // Watchdog timer configuration
    watchdog_enable(1000, true); // Enable the watchdog timer with a timeout of 1000 ms and pause on debug
    watchdog_update(); // Update the watchdog timer to prevent reset

    return 0;
}