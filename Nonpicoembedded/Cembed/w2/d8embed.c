#include <driver/gpio.h>
#include "esp_intr_alloc.h"

/* 
Offloading I/O to PIO on the Pico
The Programmable I/O (PIO) block can run simple state machines in hardware. Example: setting up a PIO state machine to generate a custom UART signal at a nonstandard baud rate.
*/

/*
Pin Debounce using a Hardware timer
Instead of busy-waiting in software, configure a one‐shot timer that fires 10–20 ms after the first edge, then sample the pin again in the timer callback to confirm a stable transition.
*/

/*
Measuring supply voltage using the ADC
Create a simple voltage divider on a GPIO ADC pin. Before reading, take multiple samples, average them, then scale back up (using the divider ratio) to compute the MCU’s supply voltage.
*/

int main(){
    // ESP32 Task affinity (Pinned Tasks) - You can pin a FreeRTOS task to a specific core:
    xTaskCreatePinnedToCore(
        myTask, "myTask", 2048, NULL, 5, NULL, 1 // Create a task pinned to core 1
    );

    // Inter-Task Communication with Queues 
    xQueueCreate(
        sizeof(int), 10 // Create a queue that can hold 10 integers
    );
    xQueueSend(
        myQueue, &data, portMAX_DELAY // Send data to the queue
    );
    xQueueReceive(
        myQueue, &data, portMAX_DELAY // Receive data from the queue
    );
    // Safely Passes Data Between Tasks without disabling interrupts.

}
