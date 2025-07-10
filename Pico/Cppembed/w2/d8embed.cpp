#include <cstdio>               // for printf
#include <cstdint>              // for uint16_t
#include "pico/stdlib.h"       // core Pico functionality
#include "hardware/gpio.h"     // GPIO API
#include "hardware/adc.h"      // ADC API
#include "hardware/watchdog.h" // Watchdog API
#include "hardware/multicore.h" // Multicore API
#include "pico/flash.h" // Flash API for persistent storage
#include "hardware/spi.h"      // SPI API

int main(){
    // SPI Clock Polarity and Phase: Configure SPI mode by setting clock polarity (CPOL) and clock phase (CPHA) in spi_set_format().
    spi_set_format(spi0, 8, SPI_CPOL_1, SPI_CPHA_1, SPI_MSB_FIRST); // Set SPI format with 8 bits per word, CPOL=1, CPHA=1 (idle high clock, capture on second edge), and MSB first

    // Using PWM Wrap and Level: Control PWM frequency and duty cycle more precisely by calling pwm_set_wrap() then pwm_set_channel_level().
    pwm_set_wrap(pwm_gpio_to_slice_num(0), 255); // Set PWM wrap value for channel 0 to 255
    pwm_set_channel_level(0, 128); // Set PWM channel 0 level to 128 (50% duty cycle)
    // The frequency = clock frequency / (wrap + 1) = 125MHz / (255 + 1) = 488.28kHz

    // Using Flash for Persistent Storage: Store a value in flash memory using flash_range_erase() and flash_range_program() from the pico/flash.h API to write small amounts of data to on-board QPSI flash, enabling non-volatile storage of configuration.
    uint32_t flash_address = 0x100000; // Example flash address
    uint32_t value_to_store = 42; // Example value to store
    flash_range_erase(flash_address, 4096); // Erase a 4KB flash sector
    flash_range_program(flash_address, &value_to_store, sizeof(value_to_store)); // Program the value into flash memory


}