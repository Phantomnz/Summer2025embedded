#include <iostream>
#pragma once
class Sensor {
public:
  virtual bool begin() = 0;             // initialize hardware
  virtual bool read() = 0;              // trigger a measurement
  virtual float getValue() const = 0;   // retrieve last measurement
  virtual ~Sensor() = default;
};
