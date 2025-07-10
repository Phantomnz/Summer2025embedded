#include <cstdio>               // for printf
#include <cstdint>              // for uint16_t
#include "pico/stdlib.h"       // core Pico functionality
#include "hardware/gpio.h"     // GPIO API
#include "hardware/adc.h"      // ADC API
#include "hardware/watchdog.h" // Watchdog API


int main(){
    // Accessing GPIO pins on the Pico W 
    gpio_init(25); // Initialize GPIO pin 25
    gpio_set_dir(25, GPIO_OUT); // Set pin 25 as output
    gpio_put(25, 1); // Set pin 25 high

    // Timers with SDK on Pico W
    sleep_ms(1000); // Wait for 1 second (1000 milliseconds)

    // UART communication on Pico W 
    // UART on the Pico W is used for serial communication. You initialize it and set the GPIO pins for TX and RX as below:
    uart_init(uart0, 115200); // Initialize UART0 with a baud rate of 115200
    gpio_set_function(0, GPIO_FUNC_UART); // Set GPIO 0 as UART TX (transmit)
    gpio_set_function(1, GPIO_FUNC_UART); // Set GPIO 1 as UART RX (receive)
}