#include <cstdio>               // for printf
#include <cstdint>              // for uint16_t
#include "pico/stdlib.h"       // core Pico functionality
#include "hardware/gpio.h"     // GPIO API
#include "hardware/adc.h"      // ADC API
#include "hardware/watchdog.h" // Watchdog API
#include "hardware/pwm.h"      // PWM API

int main() {
    // 1) Initialize all stdio (sets up USB/UART for printf)
    stdio_init_all();
    // stdio_uart_init(); // Not needed if using stdio_init_all()
    // uart_init(uart0, 115200); // Not needed unless you want to manually configure UART

    // 2) Initialize GPIO pins for UART (if needed)
    gpio_set_function(0, GPIO_FUNC_UART); // Set GPIO 0 to UART function (TX)
    gpio_set_function(1, GPIO_FUNC_UART); // Set GPIO 1 to UART function (RX)

    // 3) PWM Control (Pico W)
    gpio_set_function(2, GPIO_FUNC_PWM); // Set GPIO 2 to PWM function
    uint slice_num = pwm_gpio_to_slice_num(2); // Get the PWM slice number for GPIO 2
    pwm_set_wrap(slice_num, 255); // Set the PWM wrap value (e.g., 8-bit resolution)
    pwm_set_gpio_level(2, 128); // Set the PWM level for GPIO 2 (50% duty cycle)
    pwm_set_enabled(slice_num, true); // Enable the PWM output

    // 4) Watchdog Timer (Pico W)
    watchdog_enable(1000, 1); // Enable the watchdog timer with a timeout of 1000 ms, pause on debug 1 ms
    watchdog_update(); // Update the watchdog timer to prevent it from resetting the system
    return 0;
}