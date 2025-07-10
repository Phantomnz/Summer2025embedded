#include <iostream>
#include "SensorManager.h"
#include "Sensor.h"
#include <vector>
#include <memory>

void SensorManager::addSensor(std::unique_ptr<Sensor> s) {
    if (s && s->begin()) {
        sensors_.push_back(std::move(s));
    }
}

void SensorManager::readAll() {
    for (auto &sensor : sensors_) {
        sensor->read();
    }
}

std::vector<float> SensorManager::getAllValues() const {
    std::vector<float> vals;
    vals.reserve(sensors_.size());
    for (const auto &sensor : sensors_) {
        vals.push_back(sensor->getValue());
    }
    return vals;
}


