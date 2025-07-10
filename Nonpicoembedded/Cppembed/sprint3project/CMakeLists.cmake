cmake_minimum_required(VERSION 3.13)
project(EmbeddedSensors C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

# Add your source files (adjust paths as needed)
add_executable(sensor_demo
  src/main.cpp
  src/Sensor.cpp
  src/DHT11Sensor.cpp
  src/LDRSensor.cpp
  src/UltrasonicSensor.cpp
  src/SensorManager.cpp
  src/DataLogger.cpp
)
target_include_directories(sensor_demo PRIVATE ${CMAKE_SOURCE_DIR})
# Add any necessary libraries

# If using Pico SDK or ESP-IDF, include those toolchains accordingly
