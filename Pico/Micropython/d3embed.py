# Onboard LED PWM Fade (Pico) - Gradually increase and decrease the duty cycle to create a smooth fade effect on the pico's onboard LED.
from machine import Pin, PWM
import time
led = PWM(Pin(25))  # Use GPIO 25 for the onboard LED
led.freq(1000)  # Set frequency to 1 kHz
for duty in range(0, 65535, 2048):  # Gradually increase duty cycle
    led.duty_u16(duty)  # Set the duty cycle
    time.sleep(0.01)  # Wait for a short duration
for duty in range(65535, 0, -2048):  # Gradually decrease duty cycle
    led.duty_u16(duty)  # Set the duty cycle
    time.sleep(0.01)  # Wait for a short duration

# Debouncing a Button with Timer - An interrupt on the falling edge starts a one-shot timer; the callback checks the pin after a delay to filter out bounce noise
from machine import Pin, Timer
button = Pin(15, Pin.IN, Pin.PULL_UP)  # Use GPIO 15 for the button
timer = Timer(-1)  # Create a timer object
def debounce(timer):
    if button.value() == 0:
        print("Button pressed")

def on_button(pin):
    timer.init(mode=Timer.ONE_SHOT, period=200, callback=debounce)  # Start a one-shot timer
button.irq(trigger=Pin.IRQ_FALLING, handler=on_button)  # Set up an interrupt on the falling edge

# RTC Reading and setting - The RTC module maintains the date and time. You set it with an 8-byte tuple and read it back for timestamping or scheduled tasks
from machine import RTC
rtc = RTC()  # Create an RTC object
rtc.datetime((2025, 8, 7, 0, 12, 30, 0, 0))  # Set the date and time (year, month, day, weekday, hour, minute, second, subseconds)
print("Current RTC datetime:", rtc.datetime())  # Read and print the current date and time
