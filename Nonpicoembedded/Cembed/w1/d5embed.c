#include <driver/gpio.h>
#include "esp_intr_alloc.h"

// I²C Multi-Master Arbitration
// On both the Pico and ESP32, if two masters try to drive the bus simultaneously, hardware arbitration ensures only the one holding SDA low wins; others detect the conflict and cease until the line is free.

int main(){
    // GPIO interrupt priority
    // ESP32 supports multiple interrupt priorities, allowing you to assign different priorities to GPIO interrupts.
    // This is useful for handling critical tasks with higher priority while allowing less critical tasks to run
    // ISR for GPIO 4
    static void IRAM_ATTR gpio_isr_handler_low(void* arg) {
        // Low-priority work
    }

    // ISR for GPIO 5
    static void IRAM_ATTR gpio_isr_handler_high(void* arg) {
        // High-priority work
    }

    void app_main(void) {
        // Install the GPIO ISR service (no default flags)
        gpio_install_isr_service(0);

        // Configure GPIO4 as input with interrupt on rising edge
        gpio_config_t io_conf = {
            .pin_bit_mask = (1ULL << GPIO_NUM_4),
            .mode         = GPIO_MODE_INPUT,
            .intr_type    = GPIO_INTR_POSEDGE
        };
        gpio_config(&io_conf);

        // Configure GPIO5 as input with interrupt on rising edge
        io_conf.pin_bit_mask = (1ULL << GPIO_NUM_5);
        gpio_config(&io_conf);

        // Attach handlers with different CPU interrupt priorities:
        //   ESP_INTR_FLAG_LEVEL1 → lower priority
        //   ESP_INTR_FLAG_LEVEL3 → higher priority
        gpio_isr_handler_add(GPIO_NUM_4, gpio_isr_handler_low, NULL);
        esp_intr_alloc(ETS_GPIO_INTR_SOURCE,
                    ESP_INTR_FLAG_LEVEL1,
                    gpio_isr_handler_low,
                    NULL,
                    NULL);

        gpio_isr_handler_add(GPIO_NUM_5, gpio_isr_handler_high, NULL);
        esp_intr_alloc(ETS_GPIO_INTR_SOURCE,
                    ESP_INTR_FLAG_LEVEL3,
                    gpio_isr_handler_high,
                    NULL,
                    NULL);
    }

    // UART Hardware Flow Control
    uart_set_hw_flow_ctrl(UART_NUM_1, UART_HW_FLOWCTRL_CTS_RTS, 0); // Enable hardware flow control on UART1 with CTS/RTS
    uart_set_baudrate(UART_NUM_1, 115200); // Set UART1 baud rate to 115200
    uart_set_word_length(UART_NUM_1, UART_DATA_8_BITS); // Set UART1 data bits to 8
    uart_set_stop_bits(UART_NUM_1, UART_STOP_BITS_1); // Set UART1 stop bits to 1
    uart_set_parity(UART_NUM_1, UART_PARITY_DISABLE); // Disable parity on UART1

    //  RTC Clock Configuration
    rtc_time_synchronized(); // Synchronize RTC time
    rtc_set_time(12, 0, 0); // Set RTC time to 12:00:00
    rtc_set_date(1, 1, 2023); // Set RTC date to 1st January 2023

    


}