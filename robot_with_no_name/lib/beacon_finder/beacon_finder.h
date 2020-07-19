// Used for moving to an IR beacon
// Authors: Thomas

// External Libraries
#include <Wire.h>
#include <Adafruit_SSD1306.h>

//Internal Libraries
#include "pinout.h"

/*
* Points the robot to the beacon with uniform rotation speed, angular_speed.
* In ideal conditionss, the robot can be driven straight ahead after running this command.
* Returns false if the robot fails to pick up a signal
*/
bool pointAtBeacon(int angular_speed, Adafruit_SSD1306);


/*
* Moves the robot to the beacon at a given speed, rotating at a given angular speed,
* stopping at a distance determined by STOPPING_STRENGTH
*/
bool goToBeacon(int speed, int angular_speed, Adafruit_SSD1306);
