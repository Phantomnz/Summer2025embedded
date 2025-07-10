#include <iostream>
#include "Sensor.h"
#include "UltrasonicSensor.h"
#include "DHT11Sensor.h"

bool UltrasonicSensor::begin() {
    printf("[Ultrasonic] begin() called\n");
    // TODO: wire up Ultrasonic library
    return true; // pretend it succeeded for now
}

bool UltrasonicSensor::read() {
    printf("[Ultrasonic] read() called\n");
    // TODO: trigger an Ultrasonic sensor read
    return true; // stub
}

float UltrasonicSensor::getValue() const {
    printf("[Ultrasonic] getValue() called\n");
    // TODO: return the last read distance value
    return 0.0f; // stub value
}
