#include <iostream>
#pragma once
#include "Sensor.h"
class LDRSensor: public Sensor {
public:
  bool begin() override;
  bool read() override;
  float getValue() const override;
};