#include "Sensor.h"
#include <iostream>
#pragma once
class DHT11Sensor: public Sensor {
public:
  bool begin() override;
  bool read() override;
  float getValue() const override;
};
