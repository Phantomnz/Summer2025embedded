#include <iostream>
#include <driver/gpio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include "driver/adc.h"

int main() {
    // ESP32 Digital IO: on ESP32, you typically use the Arduino-style pinmode() and digitalWrite() functions.
    pinMode(2, OUTPUT); // Set GPIO 2 as output
    digitalWrite(2, HIGH); // Set GPIO 2 to high

    // FreeRTOS basics on ESP32: ESP32 supports multitasking with FreeRTOS. You can create tasks like so:
    xTaskCreate([](void*){
        while (true) {
            // Toggle GPIO 2 every second
            digitalWrite(2, HIGH);
            vTaskDelay(pdMS_TO_TICKS(1000));
            digitalWrite(2, LOW);
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }, "ToggleGPIO", 2048, NULL, 1, NULL);
}