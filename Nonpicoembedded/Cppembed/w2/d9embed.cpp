#include <iostream>
#include <driver/gpio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include "driver/adc.h"

int main(){
    // I2C Repeated Start
    Wire.beginTransmission(addr); // Start communication with the device at 'addr'
    Wire.write(register); // Write the register address to read from
    Wire.endTransmission(false); // Send a repeated start condition without releasing the bus
    Wire.requestFrom(addr, 2); // Request 2 bytes from the device
    byte high = Wire.read(); // Read the high byte
    byte low = Wire.read(); // Read the low byte

    // ESP32 Bluetooth LE Advertising (Async): Configure and start BLE advertising in ESP-IDF:
    esp_ble_adv_data_t advData = { name: "ESP32_Device", appearance: 0, flags: ESP_BLE_ADV_FLAG_GEN_DISC | ESP_BLE_ADV_FLAG_BREDR_NOT_SPT };
    esp_ble_gap_config_adv_data(&advdata); // Configure advertising data
    esp_ble_gap_start_advertising(&adv_params); // Start advertising with the configured parameters
}