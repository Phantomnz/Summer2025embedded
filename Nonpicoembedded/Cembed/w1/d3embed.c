#include <driver/gpio.h>
 // Real-Time Operating System (RTOS) on ESP32
xTaskCreate(task_function, "task_name", 2048, NULL, 5, NULL); // Create a new task with a stack size of 2048 bytes and priority 5
// Task function for RTOS, FreeRTOS is built into the ESP-IDF framework

int main(){
    // interrupt configuration for gpio on ESP32
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT); // Install the GPIO ISR service
    gpio_isr_handler_add(GPIO_NUM_0, gpio_isr_handler_t handler, void* arg); // Add an ISR handler for GPIO pin 0
    gpio_set_direction(GPIO_NUM_0, GPIO_MODE_INPUT); // Set GPIO pin 0 as input
    gpio_set_intr_type(GPIO_NUM_0, GPIO_INTR_ANYEDGE); // Set the interrupt type for GPIO pin 0 to any edge
    gpio_set_pull_mode(GPIO_NUM_0, GPIO_PULLUP_ONLY); // Set pull-up mode for GPIO pin 0
    gpio_intr_enable(GPIO_NUM_0); // Enable interrupts for GPIO pin 0

    delay(1000); // Delay for 1 second to allow the configuration to take effect
    uint32_t status = save_and_disable_interrupts(); // Save the current interrupt status and disable interrupts
    shared_var = 42; // Set a shared variable to 42
    restore_interrupts(status); // Restore the previous interrupt status

    gpio_set_level(GPIO_NUM_0, 1); // Set GPIO pin 0 to high
    gpio_set_level(GPIO_NUM_0, 0); // Set GPIO pin 0 to low
    gpio_intr_disable(GPIO_NUM_0); // Disable interrupts for GPIO pin 0
    gpio_isr_handler_remove(GPIO_NUM_0); // Remove the ISR handler for GPIO pin 0
    gpio_uninstall_isr_service(); // Uninstall the GPIO ISR service

    // Watchdog timer on ESP32
    esp_task_wdt_init(5, true); // Initialize the watchdog timer with a timeout of 5 seconds and panic on timeout
    esp_task_wdt_add(NULL); // Add the current task to the watchdog timer
    esp_task_wdt_reset(); // Reset the watchdog timer to prevent a timeout

    return 0; // Return 0 to indicate successful execution
}

