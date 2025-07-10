#include <iostream>
#include "Sensor.h"
#include "LDRSensor.h"
#include "DHT11Sensor.h"

bool LDRSensor::begin() {
    printf("[LDR] begin() called\n");
    // TODO: wire up LDR library
    return true; // pretend it succeeded for now
}

bool LDRSensor::read() {
    printf("[LDR] read() called\n");
    // TODO: trigger an LDR sensor read
    return true; // stub
}

float LDRSensor::getValue() const {
    printf("[LDR] getValue() called\n");
    // TODO: return the last read light intensity value
    return 0.0f; // stub value
}
