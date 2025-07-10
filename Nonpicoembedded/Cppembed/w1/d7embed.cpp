#include <iostream>
#include <driver/gpio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include "driver/adc.h"

int main(){
    // ESP32 ADC Calibration
    /*Before reading, calibrate ADC for accuracy using esp_adc_cal_characterize() with your attenuation and resolution settings, then use esp_adc_cal_raw_to_voltage() to convert raw counts to millivolts.*/
    esp_adc_cal_characterize(ADC_ATTEN1, ADC_WIDTH_BIT_12, ADC_CHANNEL_0, 0, NULL);
    esp_adc_cal_raw_to_voltage(ADC_CHANNEL_0, 0);

    // Hardware PWM on ESP32
    ledcSetup(0, 5000, 8); // Channel 0, 5kHz frequency, 8-bit resolution
    ledcAttachPin(18, 0); // Attach GPIO 18 to channel 0
    ledcWrite(0, 128); // Set duty cycle to 50% (128 out of 255)

    // ESP32 Deep sleep Wakeup by GPIO
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, 1); // Wake up on GPIO 33 high
    esp_deep_sleep_start(); // Enter deep sleep mode
}