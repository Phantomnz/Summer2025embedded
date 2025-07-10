#include <driver/gpio.h>

int main(){
    uart_init(); // Initialize UART
    uart_config_t uart_config = { // Configure UART settings
        .baud_rate = 115200, // Set baud rate to 115200
        .data_bits = UART_DATA_8_BITS, // Set data bits to 8
        .parity = UART_PARITY_NONE, // No parity
        .stop_bits = UART_STOP_BITS_1, // Set stop bits to 1
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE, // Disable hardware flow control
    };
    uart_param_config(UART_NUM_1, &uart_config); // Apply UART configuration
    uart_driver_install(UART_NUM_1, 2048, 0, 0, NULL, 0); // Install UART driver
    uart_writes_bytes(UART_NUM_1, "Hello, UART!\n", 14); // Send a message over UART

    // ADC initialization
    adc1_config_width(ADC_WIDTH_BIT_12); // Set ADC width to 12 bits
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11); // Set attenuation for channel 0 to 11 dB
    int raw = adc1_get_raw(ADC1_CHANNEL_0); // Read raw ADC value from channel 0
    printf("ADC Raw Value: %d\n", raw); // Print the raw ADC value

    // I2c initialization and communication
    i2c_config_t conf = {
    .mode = I2C_MODE_MASTER, // Set I2C mode to master
    .sda_io_num = GPIO_NUM_21, // Set SDA pin to GPIO 21
    .scl_io_num = GPIO_NUM_22, // Set SCL pin to GPIO 22
    .master.clk_speed = 100000 // Set clock speed to 100kHz
    };
    i2c_param_config(I2C_NUM_0, &conf); // Apply I2C configuration
    i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0); // Install I2C driver

    // SPI master mode initialization
    spi_bus_config_t buscfg = { .miso_io_num = 19, .mosi_io_num = 23, .sclk_io_num = 18 }; // Configure SPI bus with MISO, MOSI, and SCLK pins
    spi_bus_initialize(HSPI_HOST, &buscfg, 1); // Initialize SPI bus with high-speed host and bus configuration

    // PWM/LED brightness control
    ledc_timer_config_t timer = {
    .speed_mode = LEDC_HIGH_SPEED_MODE, // Set speed mode to high speed
    .timer_num = LEDC_TIMER_0, // Use timer 0
    .duty_resolution = LEDC_TIMER_8_BIT, // Set duty resolution to 8 bits
    .freq_hz = 5000 // Set frequency to 5000 Hz
    };
    ledc_timer_config(&timer); // Configure LEDC timer


}