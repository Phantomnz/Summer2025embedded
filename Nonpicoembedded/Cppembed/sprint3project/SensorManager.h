#include <iostream>
#pragma once
#include "Sensor.h"
#include <vector>
#include <memory>

class SensorManager {
public:
  void addSensor(std::unique_ptr<Sensor> s); // add a sensor to the manager
  void readAll();                       // call read() on each sensor
  std::vector<float> getAllValues() const; // gather most recent values
private:
  std::vector<std::unique_ptr<Sensor>> sensors_; // store sensors
};
