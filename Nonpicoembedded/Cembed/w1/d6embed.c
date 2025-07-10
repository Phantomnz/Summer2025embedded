#include <driver/gpio.h>
#include "esp_intr_alloc.h"

int main(){
    // Initialize TCP/IP stack
    tcpip_adapter_init();
    // Initialize wifi driver
    esp_event_loop_create_default();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);
    // Set wifi mode to STA
    esp_wifi_set_mode(WIFI_MODE_STA);
    // Start wifi connection
    esp_wifi_start();

    // ESP GPIO matrix
    // ANY peripheral signal can be routed to any GPIO pin
    // For example, you can remap UART TX to a non-default pin using:
    uart_set_pin(uart_num, tx_io, -1, -1, -1);
    
}