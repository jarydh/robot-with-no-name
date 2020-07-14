// Used for controlling motors
// Authors: Jaryd

// External Libraries
#include <Wire.h>
#include "pinout.h"


/*
* Take a value between -SPEED_RESOLUTION (backwards max) and SPEED_RESOLUTION (forwards max)
* Both motors will turn at the same speed in the same direction
* A value of 0 will turn both motors off
*/
void driveStraight(int speed);

/*
* Take a value between -SPEED_RESOLUTION (left turn max) and SPEED_RESOLUTION (right turn max)
* One motor turns forwards, one motor turns backwards at the set speed
* A value of 0 will turn both motors off
*/
void turn(int angular_speed);