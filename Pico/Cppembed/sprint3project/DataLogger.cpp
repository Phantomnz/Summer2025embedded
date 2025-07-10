#include "DataLogger.h"
void DataLogger::log(const std::vector<float>& values) {
    // e.g. print them:
    printf("[DataLogger] ");
    for (float v : values) printf("%.2f ", v);
    printf("\n");
}
// This is a stub for the DataLogger class that logs sensor values.