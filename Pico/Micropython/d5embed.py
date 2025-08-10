# Concurrency with uasyncio (blink + button at the same time) - uasyncio lets you schedule lightweight concurrent tasks. Here an LED blinks while a button is monitored without blocking
import uasyncio as asyncio
from machine import Pin
LED_PIN = 25 # PICO W/WH onboard LED; on ESP commonly 2
BTN_PIN = 14 # PICO W/WH onboard button; on ESP commonly 0
led = Pin(LED_PIN, Pin.OUT) # LED pin
btn = Pin(BTN_PIN, Pin.IN, Pin.PULL_UP) # Button pin
async def blink():
    while True:
        led.toggle() # Toggle LED state
        await asyncio.sleep(0.5) # Sleep for 500ms

async def button_monitor():
    while True:
        if not btn.value(): # If button is pressed (active low)
            print("Button pressed")
            await asyncio.sleep(0.5) # Debounce delay
        await asyncio.sleep(0.02) # Sleep for 20ms
async def main():
    await asyncio.gather(blink(), button_monitor())
asyncio.run(main()) # Run the main function

# HTTP GET with urequests (after Wi-Fi connect) - Connect to Wi-Fi, then fetch a web page. urequests is a tiny HTTP client for MicroPython; install it with mip if it's not bundled
import network, time 
# if urequests is missing: import mip; mip install("urequests")
import urequests as requests

SSID, PASS = "your_SSID", "your_PASSWORD" # Wi-Fi credentials
wlan = network.WLAN(network.STA_IF) # Create a WLAN station interface
wlan.active(True) # Activate the interface
wlan.connect(SSID, PASS) # Connect to the Wi-Fi network
while not wlan.isconnected(): # Wait for connection
    time.sleep(1) # Sleep for 1 second

r = requests.get("http://example.com") # Replace with your URL
print(r.status_code, len(r.text)) # Print status code and length of response
r.close() # Close the response to free resources

# MQTT Publish/Subscribe with umqtt.simple - MQTT is perfect for IoT telemetry. This connects to a public broker, subscribes, publishes once, then briefly listens for messages.
# If umqtt.simple is missing: import mip; mip install("umqtt.simple")
import umqtt.simple as MQTTClient
import network, time
broker = "broker.hivemq.com" # MQTT broker address
topic = b"pico-demo/topic" # MQTT topic
def on_msg(topic, msg): # Callback function for received messages
    print("RX:", topic, msg) # Callback for received messages

client = MQTTClient(client_id="mp-demo", server=broker, port=1883, keepalive=30) # Create MQTT client
client.set_callback(on_msg) # Set the callback function
client.connect() # Connect to the MQTT broker
client.subscribe(topic) # Subscribe to the MQTT topic
client.publish(topic, b"Hello MQTT") # Publish a message to the topic

start = time.ticks_ms() # Get current time in milliseconds
while time.ticks_diff(time.ticks_ms(), start) < 5000: # Listen for messages for 5 seconds
    client.check_msg() # Check for incoming messages

client.disconnect() # Disconnect from the MQTT broker

# Sync RTC with NTP (ntptime) - ntptime contacts an NTP server and sets your board's clock to UTC. Apply your timezone in code when displaying or logging
import ntptime, time
ntptime.settime() # Set the RTC to the current time from the NTP server
print("RTC set to:", time.localtime()) # Print the current time in local format
# to apply a timezone offset (e.g. +3 hours), manually adjust when printing.

# Drive NeoPixels / WS2812 LEDs - The neopixel module sends the correct timing for WS2812/NeoPixel strips. Set each LED's (R,G,B) and call write() to latch
from machine import Pin
import neopixel
NP_PIN = 16 # Choose a GPIO with a direct wire to the strip
NUM = 8 # number of LEDs on your strip
np = neopixel.NeoPixel(Pin(NP_PIN), NUM) # Create NeoPixel object
# Fill red then write once:
for i in range(NUM):
    np[i] = (255, 0, 0) # Set each LED to red
np.write() # Write the changes to the strip
time.sleep(1) # Wait for 1 second
# Wipe to off:
for i in range(NUM):
    np[i] = (0, 0, 0) # Set each LED to off
np.write() # Write the changes to the strip