// Used for moving to an IR beacon
// Authors: Thomas, Jaryd

// External Libraries
#include <Wire.h>
// #include <Adafruit_SSD1306.h>

//Internal Libraries
#include "pinout.h"
#include "sonar.h"

/*
* Points the robot to the beacon with uniform rotation speed, angular_speed.
* In ideal conditionss, the robot can be driven straight ahead after running this command.
* Returns false if the robot fails to pick up a signal
*/
bool pointAtBeacon(int angular_speed, Adafruit_SSD1306 display);

/*
* Does PID control to allign the robot with the beacon
* Returns false if PID fails
*/
bool pidToBeacon(Adafruit_SSD1306 display, sonarWrapper sonar);

void setPIDMotors(int speed);

/*
* Used for debugging IR, just prints readings to the display
*/
void IRDebug(Adafruit_SSD1306 display);
