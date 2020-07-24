// Used for controlling motors
// Authors: Jaryd

#ifndef MOTORS_H
#define MOTORS_H

// External Libraries
#include <Wire.h>
#include <pinout.h>

enum motorSides
{
    LEFT,
    RIGHT
};

/*
* Take a value between -SPEED_RESOLUTION (backwards max) and SPEED_RESOLUTION (forwards max)
* Both motors will turn at the same speed in the same direction
* A value of 0 will turn both motors off
*/
void driveStraight(int speed);

/*
* Turns both motors off
*/
void stop();

/*
* Take a value between -SPEED_RESOLUTION (left turn max) and SPEED_RESOLUTION (right turn max)
* One motor turns forwards, one motor turns backwards at the set speed
* A value of 0 will turn both motors off
*/
void turn(int angular_speed);

/*
* Drives a single motor at a given speed (0 to 1000)
*/
void driveMotor(PinName motor, int speed);

/*
* Drives a single motor at a given speed (-1000 to 1000)
*/
void setMotorSpeed(motorSides side, int speed);


#endif
