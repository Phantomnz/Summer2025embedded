# Touch Pad Input (ESP32) - The TouchPad class reads capacitive touch input. You configure a sensitivity threshold, then read() returns higher values when touched
from machine import TouchPad, Pin
touch = TouchPad(Pin(4))  # Use GPIO 4 for touch input
touch.config(400)  # Set sensitivity threshold (0-255)
value = touch.read()  # Read the touch value
print("Touch value:", value)  # Print the touch value

# Using network for Wi-Fi (ESP32) - The network module manages Wi-Fi. STA_IF is station mode. You activate, connect to an AP (Access Point), and poll until you're online
import network
wlan = network.WLAN(network.STA_IF)  # Create a station interface
wlan.active(True)  # Activate the interface
wlan.connect('your-ssid', 'your-password')  # Connect to the Wi-Fi network
while not wlan.isconnected():  # Wait until connected
    pass  # Poll until connected
print("Connected to Wi-Fi, IP:", wlan.ifconfig()[0])  # Print the network configuration
