// Code for finding cans
// Authors: Jaryd

#ifndef CAN_FINDER_H
#define CAN_FINDER_H

#include <Arduino.h>
#include <Ultrasonic.h>
#include <Adafruit_SSD1306.h>


#include "motors.h"
#include "pinout.h"

// For every 1cm of range, we get 56us of timeout
// #define TIMEOUT_TO_RANGE_SLOPE 56

class CanFinder
{
public:
    // Constructor
    CanFinder(Ultrasonic &sonar, Adafruit_SSD1306 &display)
        : sonar(sonar), display(display) {}

    /*
        Detect and drive towards can until it is in CAN_STOP_RANGE distance.
    */
    bool find_can();

    /*
        Returns true if sucessfully grabbed a can
    */
    bool check_can();


private:
    /*
        Reads from the sonar sensor until a reasonable value is obtained.
    */
    int read_sonar();
    int last_sonar;
    Ultrasonic &sonar;
    Adafruit_SSD1306 &display;
};

#endif
