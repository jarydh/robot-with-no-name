// Code for finding cans
// Authors: Jaryd

#ifndef CAN_FINDER_H
#define CAN_FINDER_H

#include <Arduino.h>
#include <Ultrasonic.h>

#include "motors.h"
#include "pinout.h"

// For every 1cm of range, we get 56us of timeout
// #define TIMEOUT_TO_RANGE_SLOPE 56

class CanFinder
{
public:
    // Constructor
    CanFinder(Ultrasonic &sonar)
        : sonar(sonar) {}

    /*
        Detect and drive towards can until it is in CAN_STOP_RANGE distance.
    */
    bool find_can();

private:
    /*
        Reads from the sonar sensor until a reasonable value is obtained.
    */
    int read_sonar();

    Ultrasonic &sonar;
};

#endif
