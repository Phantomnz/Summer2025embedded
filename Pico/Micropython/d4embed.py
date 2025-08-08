# UART Serial (TX/RX) - machine.UART sets up serial comms. Pick a UART ID and hook it to valid TX/RX pins. write() sends bytes; readline() grabs a line if available.
from machine import UART, Pin
# PICO: UART0 on GP0 (TX) and GP1 (RX)
uart = UART(0, baudrate=115200, tx=Pin(0), rx=Pin(1))
# ESP32 Example (choose pins that support UART; here GPIO16 (TX) and GPIO17 (RX))
# uart = UART(2, baudrate=115200, tx=Pin(16), rx=Pin(17))

uart.write(b"Hello, UART!\n")
if uart.any(): # Check if any data is available to read
    line = uart.readline() # Read a line from the UART
    print("RX:", line) # Print the received line

# Periodic Timer (blinky without blocking) - A hardware timer calls tick() at a fixed period, letting you toggle an LED (or run other jobs) without sleep() blocking the main thread.
from machine import Pin, Timer
led = Pin(25, Pin.OUT)  # PICO: GP25 is the onboard LED; ESP32: use Pin(2) on many boards
t = Timer(-1) # Create a timer object

def tick(timer):
    led.toggle()  # Toggle the LED state

# 200 ms periodic interrupt
t.init(period=200, mode=Timer.PERIODIC, callback=tick)

# I2C Register Helpers (read/write a device register) - Many sensors use simple register protocols. Write the register address, then read bytes back. These helpers work across devices (just change address/regs)
from machine import I2C, Pin
# PICO I2C0: SCL = GP21, SDA = GP20 (adjust to your wiring)
i2c = I2C(0, scl=Pin(21), sda=Pin(20), freq = 400_000)
DEV_ADDR = 0x68 # example: IMU / RTC address
WHO_REG = 0x75 # example: WHO_AM_I register

def reg_read(addr, reg, n=1):
    i2c.writeto(addr, bytes([reg]))  # Write the register address
    return i2c.readfrom(addr, n)  # Read n bytes from the device

def reg_write(addr, reg, data: bytes):
    i2c.writeto(addr, bytes([reg]) + data)  # Write the register address and data

who = reg_read(DEV_ADDR, WHO_REG, 1) # Read the WHO_AM_I register and print the result
print("WHO_AM_I:", who[0])  # Print the first byte of the response

# Watchdog Timer (auto-reset on lockups) - If your code hangs and stops calling feed(), the MCU (Microcontroller Unit) will reset after timeout ms. Great for unattended/field devices
from machine import WDT
import time
wdt = WDT(timeout=5000)  # Set watchdog timeout to 5 seconds
for i in range(10):
    # do useful work here...
    time.sleep(0.3) # sleep for 300 ms
    wdt.feed()  # Reset the watchdog timer before it expires
    print("fed", i)

# boot.py vs. main.py (startup flow) - On reset, boot.py executes first (environment/config). Then main.py runs (your app). This seperation keeps config stable while you iterate on the app

# boot.py - runs first on reset; setup system (e.g., Wi-Fi, paths)
import sys
sys.path.append('/lib')  # Add /lib to the module search path
# (optional) Set Wi-Fi creds here on ESP32, mount sd etc.

# main.py - your application logic
from machine import Pin
led = Pin(25, Pin.OUT)  # PICO: GP25 is the onboard LED; ESP32: use Pin(2) on many boards
led.value(1)  # Turn on the LED
print("app started")
