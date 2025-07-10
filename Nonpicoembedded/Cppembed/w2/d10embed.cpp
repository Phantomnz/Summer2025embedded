#include <iostream>
#include <driver/gpio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include "driver/adc.h"

// If your embedded project grows, list multiple source files explicitly in the CMakeLists.txt file.

int main() {
    // ESP32 I2S Audio Output: Configure I2S for audio output on ESP32 using:
    i2s_config_t cfg = {
        .mode = I2S_MODE_MASTER | I2S_MODE_TX, // I2S mode: master transmitter
        .sample_rate = 44100, // Sample rate in Hz
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT, // Bits per sample
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT, // Stereo format
    };
    i2s_driver_install(I2S_NUM_0, &cfg, 0, NULL); // Install I2S driver

    //ESP32 Deep Sleep with RTC memory: Store state across deep sleep cycles using RTC memory.
    RTC_DATA_ATTR int bootCount = 0; // RTC memory variable to retain state
    void app_main(){
        bootCount++; // Increment boot count
        printf("Boot count: %d\n", bootCount); // Print boot count
    }
}