#include <driver/gpio.h>
#include "esp_intr_alloc.h"

int main(){
    // ESP32 PWM Frequency control

    ledc_timer_config_t timer = {
        .speed_mode = LEDC_HIGH_SPEED_MODE, // Use high-speed mode
        .duty_resolution = LEDC_TIMER_10_BIT, // Set resolution to 10 bits
        .timer_num = LEDC_TIMER_0, // Use timer 0
        .freq_hz = 5000, // Set frequency to 5 kHz
        .clk_cfg = LEDC_AUTO_CLK, // Use automatic clock configuration
    };
    ledc_timer_config(&timer);
    // Attach channel 0 to GPIO 18
    ledc_channel_config_t ch = {
        .channel = LEDC_CHANNEL_0, // Use channel 0
        .duty = 512, // Set duty cycle to 512 (50% of 1024)
        .gpio_num = 18, // Use GPIO 18
        .speed_mode = LEDC_HIGH_SPEED_MODE, // Use high-speed mode
        .hpoint = 0, // Set hpoint to 0
        .timer_sel = LEDC_TIMER_0, // Use timer 0
    };
    ledc_channel_config(&ch);

    touch_pad_initialize(); // Initialize touch pad
    touch_pad_config(TOUCH_PAD_NUM0, 0); // Configure touch pad 0 with threshold 0
    esp_sleep_enable_touchpad_wakeup(); // Enable touch pad wakeup
    esp_deep_sleep_start(); // Start deep sleep
}