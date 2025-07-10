#include <iostream>
#pragma once
#include <vector>
class DataLogger {
public:
  void log(const std::vector<float>& values);
  // could write to serial, SD card, or queue
};
