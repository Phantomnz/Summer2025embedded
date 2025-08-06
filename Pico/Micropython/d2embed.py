# PWM on MicroPython - PWM objects let you generate analog-like signals for LEDs, motors, or buzzers by setting frequency and duty cycle.
from machine import Pin, PWM
pwm = PWM(Pin(15)) # Create a PWM object on pin 15
pwm.freq(1000)  # Set frequency to 1000 Hz
pwm.duty_u16(32768)  # Set duty cycle to 50% (range is 0-65535)

# I2C Communication - Initialize I2C on specified pins and scan for attached devices. On ESP32 use I2C(1, ...) and appropriate pins.
from machine import I2C, Pin
i2c = I2C(0, scl=Pin(21), scl=Pin(20), freq=400000)  # Create I2C object with specified pins and frequency
devices = i2c.scan()  # Scan for devices on the I2C bus
print("I2C devices found:", devices)  # Print found I2C devices

# SPI Communication - Configure SPI bus parameters and pins. readinto reads 2 bytes into the buffer, sending 0xFF as MOSI data
from machine import SPI, Pin
spi = SPI(0, baudrate=1000000, polarity=0, phase=0, sck=Pin(2), mosi=Pin(3), miso=Pin(4))  # Create SPI object with specified parameters
buf = bytearray(2)  # Create a buffer for 2 bytes
spi.readinto(buf, 0xFF)  # Read 2 bytes into the buffer, sending 0xFF as MOSI data
print("SPI read data:", buf)  # Print the received data from SPI

# Deep Sleep and Wake on Timer - Use the RTC to schedule a wake-up alarm and enter deep sleep mode to conserve power. The board rests upon wake
import machine, time
rtc = machine.RTC()  # Create RTC object
rtc.irq(trigger=rtc.ALARM0, wake=machine.DEEPSLEEP)  # Set an alarm to wake up from deep sleep
rtc.alarm(rtc.ALARM0, 10000)  # Set alarm to trigger in 10 seconds
print("Entering deep sleep for 10 seconds...")
machine.deepsleep()  # Enter deep sleep mode
# after 10 seconds, the board will wake up automatically

# Reading and Writing files - The on-device filesystem supports standard file I/O. Use open in "w" or "r" modes to write or read text files.
with open("test.txt", "w") as f: # Open file in write mode
    f.write("Hello, MicroPython!")  # Write text to the file
with open("test.txt", "r") as f:  # Open file in read mode
    content = (f.read())  # Read the content of the file
