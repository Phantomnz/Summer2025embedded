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

// On both the Pico and ESP32, if 2 masters try to drive the bus simultaneously, hardware arbitration ensures only the one holding SDA low can continue to drive it.
// other masters will wait until the bus is free before attempting to drive it again.

// UART Hardware flow control:
// Hardware RTS (Request to Send) and CTS (Clear to Send) lines are used for hardware flow control.
// It isn't built into the RP2040, but can be implemented using spare GPIO pins.

// RTC (Real-Time Clock):
// The RP2040 does not have a built-in RTC, but you can use an external RTC chip like the DS3231 or PCF8563, attached via I2C.
// or count using your own low power timer with calibration

#define NUM_SAMPLES 16

int main() {
    stdio_init_all();

    // Buffer to hold samples
    uint16_t samples[NUM_SAMPLES];

    // Initialize ADC hardware
    adc_init();
    // Enable round-robin sampling on channels 0, 1 and 2
    adc_set_round_robin(true);
    adc_set_round_robin_mask((1 << 0) | (1 << 1) | (1 << 2));

    // Configure ADC FIFO: enable, set DREQ pacing, no error bit, 1 sample before IRQ
    adc_fifo_setup(
        true,    // write each sample to FIFO
        true,    // enable DMA request (DREQ)
        1,       // number of samples to collect before raising DREQ
        false,   // don't use ERR bit
        false    // don't shift samples
    );

    // Claim a free DMA channel
    int dma_chan = dma_claim_unused_channel(true);
    dma_channel_config cfg = dma_channel_get_default_config(dma_chan);

    // Configure the channel:
    //  - transfer 16-bit samples
    //  - read from ADC FIFO (no increment)
    //  - write into our buffer (increment)
    channel_config_set_transfer_data_size(&cfg, DMA_SIZE_16);
    channel_config_set_read_increment(&cfg, false);
    channel_config_set_write_increment(&cfg, true);
    // Pace transfers by ADC FIFO DREQ
    channel_config_set_dreq(&cfg, DREQ_ADC);

    // Configure and start the DMA transfer
    dma_channel_configure(
        dma_chan,
        &cfg,
        samples,                  // Destination pointer
        &adc_hw->fifo,            // Source pointer (ADC FIFO register)
        NUM_SAMPLES,              // Number of samples to transfer
        true                      // Start immediately
    );

    // Now let the ADC+DMA run in the background...
    while (true) {
        // Optionally, wait for DMA to finish
        dma_channel_wait_for_finish_blocking(dma_chan);

        // Process the samples array
        for (int i = 0; i < NUM_SAMPLES; ++i) {
            printf("Sample %2d = %4d\n", i, samples[i]);
        }

        sleep_ms(1000);

        // Restart the transfer for another round
        dma_channel_start(dma_chan);
    }
}

