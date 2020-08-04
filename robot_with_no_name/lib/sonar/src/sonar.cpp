// Code for finding cans
// Authors: Jaryd

#include "sonar.h"

#include "sensor_math.h"

// Sonar values
const int num_sonar_readings = NUM_SONAR_READINGS;

// For every 1cm of range, we get 56us of timeout
#define TIMEOUT_TO_RANGE_SLOPE 56

int sonarWrapper::readSonar()
{
    pushNewData(sonar_readings, sonar_ptr.read(), num_sonar_readings);
    return median(sonar_readings, num_sonar_readings);
}

void sonarWrapper::resetSonar()
{
    for(int i = 0; i < num_sonar_readings; i++)
    {
        sonar_readings[i] = sonar_ptr.read();
    }
}

/*
* Takes a sonar object pointer and a range in cm to set the sonar range to.
*/
void sonarWrapper::setSonarRange(int range)
{
    sonar_ptr.setTimeout(range * TIMEOUT_TO_RANGE_SLOPE);
}
