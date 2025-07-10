#include <pico/stdlib.h>
#include "hardware/adc.h" 
#include "hardware/i2c.h"
#include <stdint.h> // for uint32_t
#include <stdio.h> // for printf
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "hardware/pwm.h"
#include "hardware/dma.h"
#include "hardware/watchdog.h"
#include "hardware/irq.h"
#include "pico/time.h"
#include "pico/flash.h"

// PI PICO PIO UART Receiver: Use a PIO state machine to implement a UART receiver on an arbitrary GPIO pin, freeing up the UART hardware for other uses.

int main(){
    // Pico Flash Memory Access: Read/Write onboard QPSI flash with the flash.h API:
    flash_range_erase(0x100000, 0x1000); // Erase a range of flash memory
    flash_range_program(0x100000, (const uint8_t *)"Hello, Flash!", 13); // Write data to flash memory
}

