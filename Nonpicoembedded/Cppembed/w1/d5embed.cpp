#include <iostream>
#include <driver/gpio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include "driver/adc.h"

// Task function: prints a message every second
void TaskBlink(void* pvParameters) {
    while (1) {
        printf("Hello from TaskBlink!\n");
        vTaskDelay(pdMS_TO_TICKS(1000));  // sleep 1000 ms
    }
}

extern "C" void app_main() {
    // Create a FreeRTOS task:
    xTaskCreate(
        TaskBlink,               // function
        "BlinkTask",             // name
        2048,                    // stack size (bytes)
        nullptr,                 // parameters
        tskIDLE_PRIORITY + 1,    // priority
        nullptr                  // task handle
    );

        // 1) Configure ADC1, 12-bit width
    adc1_config_width(ADC_WIDTH_BIT_12);
    // 2) Configure channel attenuation (e.g. ADC_CHANNEL_6 = GPIO34)
    adc1_config_channel_atten(ADC_CHANNEL_6, ADC_ATTEN_DB_11);

    while (1) {
        // 3) Read raw ADC value (0–4095)
        int raw = adc1_get_raw(ADC_CHANNEL_6);
        printf("ADC Channel 6 Raw: %d\n", raw);
        vTaskDelay(pdMS_TO_TICKS(500));  // 500 ms between readings
    }
}

/*
Optimizing Flash Memory Usage
For embedded systems, reduce code size by using -Os with GCC to optimize for size. This is useful when flash memory is limited.*/
