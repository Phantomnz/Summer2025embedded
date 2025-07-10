#include <driver/gpio.h>
#include "esp_intr_alloc.h"

int main() {
    // ESP32 ADC Attenuation: Configure ADC attenuation for different voltage ranges
    adc1_config_channel_atten(ADC1_channel_6, ADC_ATTEN_DB_11); // Set attenuation for ADC1 channel 6 to 11 dB

    // ESP32 RTC (Real-Time Clock) Memory: Preserve variables across deep sleep by placing them in RTC memory
    RTC_DATA_ATTR int boot_count = 0; // Variable to keep track of boot count across deep sleep

    // LEDC Fade API (ESP32): Smoothly ramp PWM duty without CPU loops
    ledc_fade_func_install(0); // Install the LEDC fade function
    ledc_set_fade_with_time(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, 255, 1000); // Set fade to 255 duty cycle over 1000 ms
    ledc_fade_start(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, LEDC_FADE_NO_WAIT); // Start the fade without waiting
}