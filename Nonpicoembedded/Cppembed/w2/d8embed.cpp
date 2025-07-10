#include <iostream>
#include <driver/gpio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include "driver/adc.h"

int main(){
    // I2C Bus Scanning (ESP32): Perform a scan to detect connected I2C devices. Loop through addresses 0x03 to 0x77 and use Wire.beginTransmission() and endTransmission() -- a zero return means a device is present at that address.
    wire.beginTransmission(0x3C); // Example address
    if (wire.endTransmission() == 0) {
        std::cout << "Device found at address 0x3C" << std::endl;
    } else {
        std::cout << "No device found at address 0x3C" << std::endl;
    }
    wire.endTransmission(); // End the transmission

    // ESP32 Task notification for ISR-to-Task signaling: instead of using semaphores, you can use task notifications to signal a task from an ISR. This is more efficient and avoids the overhead of semaphore operations
    xTaskNotifyFromISR(
        myTaskHandle, // Task handle to notify
        0, // Notification value
        eSetValueWithOverwrite, // Overwrite the previous value
        NULL // No need for a higher priority task notification
    );
}