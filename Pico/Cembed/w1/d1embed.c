#include <pico/stdlib.h>

int main(){
    stdio_init_all(); // Initialize standard input/output
    gpio_init(); // Initialize GPIO
    gpio_set_dir(); // Set GPIO direction
    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true) {
    gpio_put(LED_PIN, 1);
    sleep_ms(500);
    gpio_put(LED_PIN, 0);
    sleep_ms(500);
}
//Memory Constraints
//Embedded microcontrollers have limited RAM (e.g., Pico has 264 KB, ESP32 ~520 KB). Keep stack usage small and prefer static/global buffers when necessary.

// Hardware Abstraction
//Both platforms offer SDK functions to abstract low-level registers. Use these so your code is more portable and maintainable.

