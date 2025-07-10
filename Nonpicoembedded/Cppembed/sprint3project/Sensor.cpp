#include "Sensor.h"
#include <iostream>

// DHT11Sensor.cpp
#include "DHT11Sensor.h"

bool Sensor::begin() {
  // TODO: wire up library
  return true; // pretend it succeeded for now
}

bool Sensor::read() {
  // TODO: trigger a sensor read
  return true; // stub
}

float Sensor::getValue() const {
  // TODO: return the last read value
  return 0.0f; // stub value
}
