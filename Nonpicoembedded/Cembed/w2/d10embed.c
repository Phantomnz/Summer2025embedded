#include <driver/gpio.h>
#include "esp_intr_alloc.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"

// ESP32 Wifi Scan Example
void scan(){
    wifi_scan_config_t cfg = { .show_hidden = true}; // Configuration for the scan
    esp_wifi_scan_start(&cfg, true); // Start the scan and wait for it to complete
    uint16_t ap_num; // Variable to hold the number of access points found
    esp_wifi_scan_get_ap_num(&ap_num); // Get the number of access points found
    wifi_ap_record_t *ap_list = malloc(sizeof(wifi_ap_record_t) * ap_num); // Allocate memory for the access point records
    for (int i = 0; i < ap_num; i++) {
        printf("SSID: %s, RSSI: %d\n", ap_list[i].ssid, ap_list[i].rssi); // Print the SSID and RSSI of each access point
    }
    free(ap_list); // Free the allocated memory for the access point records
}

void app_main(){
    esp_netif_init(); // Initialize the network interface
    esp_event_loop_create_default(); // Create the default event loop
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT(); // Initialize the WiFi configuration
    esp_wifi_init(&cfg); // Initialize the WiFi driver with the configuration
    esp_wifi_set_mode(WIFI_MODE_STA); // Set the WiFi mode to Station (STA)
    esp_wifi_start(); // Start the WiFi driver
    scan(); // Call the scan function to scan for WiFi networks
}


int main(){
    // Wifi Scan function
    app_main(); // Call the main application function

    // ESP32 GPIO Matrix Remapping: You can route peripheral signals (e.g. UART TX) to almost any GPIO pin.
    // Route UART0 TXD to GPIO17
    uart_set_pin(UART_NUM_0, 17, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}