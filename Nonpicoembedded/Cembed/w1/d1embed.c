#include <driver/gpio.h>

int main{
    gpio_init();
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (1) {
        gpio_put(LED_PIN, 1); // Turn on LED
        sleep_ms(500);        // Wait for 500 milliseconds
        gpio_put(LED_PIN, 0); // Turn off LED
        sleep_ms(500);        // Wait for 500 milliseconds
    }
}
