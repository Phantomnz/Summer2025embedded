# On your host machine’s terminal:
# screen /dev/ttyUSB0 115200
# You’ll see the MicroPython >>> prompt.
# Use a serial terminal (e.g. screen on Unix, PuTTY on Windows) at 115200 baud to interactively run MicroPython commands on your board

# Filesystem Basics with os (or uos in MicroPython) - Micropython exposes os (alias uos) for basic file and directory operations on the on-board filesystem or mounted SD cards
import os
os.listdir()  # List files in the current directory
os.mkdir('testdir')  # Create a new directory named 'testdir'
os.remove('old.txt')  # Remove a file named 'old.txt'

# Controlling a GPIO Pin - Pin Objects let you configure direction and state. On the Pico WH, GPIO 25 drives the onboard LED. On ESP32, GPIO 2 is often used for the onboard LED (use a suitable pin for your board).
from machine import Pin
led = Pin(25, Pin.OUT)  # Create a Pin object for GPIO 25 as an output
led.value(1)  # Set the pin high (turn on the LED)
led.value(0)  # Set the pin low (turn off the LED)

# Reading an Analog Value - ADC reads 16-bit values from analog pins. On ESP32, use ADC(Pin(36)) or similar, and call .read() for 12 bit resolution.
from machine import ADC
pot = ADC(26)
reading = pot.read_u16()  # Read a 16-bit value from the ADC pin
print(reading)  # Print the ADC reading

# Simple delay with time.sleep_ms - Unlike time.sleep() in desktop Python, MicroPython provides sleep_ms() and sleep_us() for millisecond and microsecond delays suited to real-time control.
import time
for i in range(5):
    print("Tick", i)
    time.sleep_ms(1000)  # Sleep for 1000 milliseconds (1 second)

