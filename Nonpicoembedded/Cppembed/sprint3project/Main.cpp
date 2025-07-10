#include "SensorManager.h"
#include "DataLogger.h"
#include "DHT11Sensor.h"
#include "LDRSensor.h"
#include "UltrasonicSensor.h"
int main() {
  SensorManager manager;
  DataLogger logger;
// Create and register your sensors
    manager.addSensor(std::make_unique<DHT11Sensor>(/* any pins or config */));
    manager.addSensor(std::make_unique<LDRSensor>(/* ADC channel */));
    manager.addSensor(std::make_unique<UltrasonicSensor>(/* trigger/echo pins */));

    // Read and log in a simple loop
    manager.readAll();
    auto values = manager.getAllValues();
    logger.log(values);
    return 0;
}
// This is a stub for the main function of a C++ program that uses a SensorManager and DataLogger.