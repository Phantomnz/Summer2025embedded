// technically day 1 but C++ embed for ESP32 wasn't given for day 1
// ESP32 version: This project is designed for the ESP32 platform.

#include <iostream>
#include <driver/gpio.h>

int main() {
    // i2c on ESP32
    i2c_param_config(I2C_NUM_0, &i2c_config); // Initialize I2C with the given configuration
    i2c_config_t i2c_config = {
        .mode = I2C_MODE_MASTER, // Set I2C mode to master
        .sda_io_num = GPIO_NUM_21, // SDA pin 
        .scl_io_num = GPIO_NUM_22, // SCL pin
        .master.clk_speed = 100000 // Clock speed in Hz
    }; // Configure I2C parameters
    i2c_driver_install(I2C_NUM_0, &i2c_config); // Install the I2C driver
    i2c_master_write(I2C_NUM_0, 0x3C, data, length, portMAX_DELAY); // Write data to the I2C device
    i2c_master_read(I2C_NUM_0, 0x3C, data, length, portMAX_DELAY); // Read data from the I2C device

    // Deep sleep wakeup (ESP32)
    esp_sleep_enable_timer_wakeup(1000000); // Enable deep sleep wakeup after 1 second (1000000 microseconds)
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_0, 1); // Enable wakeup from deep sleep on GPIO 0 (high level)
    esp_deep_sleep_start(); // Start deep sleep mode
}