#include <iostream>
#pragma once
#include "Sensor.h"
class UltrasonicSensor: public Sensor {
public:
  bool begin() override;
  bool read() override;
  float getValue() const override;
};