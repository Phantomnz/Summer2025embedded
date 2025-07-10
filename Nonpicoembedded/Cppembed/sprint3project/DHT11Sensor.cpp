#include <iostream>
#include "Sensor.h"
#include "DHT11Sensor.h"

// DHT11Sensor.cpp
#include "DHT11Sensor.h"

bool DHT11Sensor::begin() {
    printf("[DHT11] begin() called\n");
    // TODO: wire up DHT library
    return true; // pretend it succeeded for now
}

bool DHT11Sensor::read() {
    printf("[DHT11] read() called\n");
    // TODO: trigger a sensor read
    return true; // stub
}

float DHT11Sensor::getValue() const {
    printf("[DHT11] getValue() called\n");
    // TODO: return the last read humidity or temperature
    return 0.0f; // stub value
}
