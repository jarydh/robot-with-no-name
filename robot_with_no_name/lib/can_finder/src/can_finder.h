// Code for finding cans
// Authors: Jaryd

#ifndef CAN_FINDER_H
#define CAN_FINDER_H

#include <Arduino.h>
#include <Ultrasonic.h>

#define NUM_SONAR_READINGS 3

class canFinder
{
public:
    // Constructor
    canFinder(Ultrasonic &sonar)
        : sonar_ptr(sonar) {}
    bool findCan();

private:
    bool sweep(bool is_clockwise, int range);
    bool driveToCan(bool is_clockwise);
    void setSonarRange(int range);
    int readSonar();
    void resetSonar();
    int sonar_readings[NUM_SONAR_READINGS];
    Ultrasonic &sonar_ptr;
    int sweep_range;
};

#endif
