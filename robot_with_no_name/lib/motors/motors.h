// Used for controlling motors
// Authors: Jaryd

#ifndef MOTORS_H
#define MOTORS_H

// External Libraries
#include <Wire.h>
#include <pinout.h>

#include "sensor_math.h"

/*
* Sets motor speed based on both speed and angular_speed, where speed increases power to both motors in the same direction,
* and angular_speed increases it in opposite directions, where positive values are clockwise.
*
* Inputs:
*       speed: a value between -SPEED_RESOLUTION (backwards max) and SPEED_RESOLUTION (forwards max).
*       angular_speed: a value between -SPEED_RESOLUTION (left turn max) and SPEED_RESOLUTION (right turn max).
*/
void drive(int speed, int angular_speed);

/*
* Turns both motors off
*/
void stop();

[[deprecated("Replaced by drive()")]] void driveStraight(int speed);

[[deprecated("Replaced by drive()")]] void turn(int angular_speed);

/*
* Delivers a quick impulse in the opposite direction to quickly stop the robot
* speed and angular_speed should be the last speed commands issued.
*/
void hard_stop();

#endif
