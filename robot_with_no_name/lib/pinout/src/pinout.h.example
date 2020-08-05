//I've had some trouble with updates to this file not being recognized.
//If you expereience this, right click on a place where a pin is referenced and select "go to defintion"
//Then you'll find a sneaky copy of this file that PIO keeps in the background.
//Try updating that as well.

/* Reserved pins:
* Display: B6, B7
* Flashing: A9, A10
*/

#ifndef PINOUT_H
#define PINOUT_H

// motors
#define LEFT_MOTOR_FORWARD_PIN PB_0
#define LEFT_MOTOR_BACKWARD_PIN PB_1
#define RIGHT_MOTOR_FORWARD_PIN PB_8
#define RIGHT_MOTOR_BACKWARD_PIN PB_9

// need integer types for Arduino-based libraries
#define LEFT_MOTOR_FORWARD_PIN_INT PB0
#define LEFT_MOTOR_BACKWARD_PIN_INT PB1
#define RIGHT_MOTOR_FORWARD_PIN_INT PB8
#define RIGHT_MOTOR_BACKWARD_PIN_INT PB9

// beacon finding phototransistors
#define IR_LEFT PA4
#define IR_RIGHT PA5

// Sonar pins
#define SONAR_ECHO_PIN PA0
#define SONAR_TRIGGER_PIN PA1

// Servo pins
#define CLAW_ARMS_SERVO_PIN_INT PA3
#define CLAW_PIVOT_SERVO_PIN_INT PA2

#define CLAW_ARMS_SERVO_PIN PA_3
#define CLAW_PIVOT_SERVO_PIN PA_2

#define START_BUTTON PA6

// config for robot

/// Motors
// value of 1 for motor off as 0 causes unwanted behaviour
#define MOTOR_OFF 1
// PWM frequency should be as low as possible without causing significant oscillation of the motor's power output
#define PMWFREQ 256

// positive values make it turn more right, negative more left. Adjust until movement is straight.
// note that large values may cause odd behaviour at very low speeds.
#define MOTOR_OFFSET 250

// Min and max PWM values
#define MIN_MOTOR_PWM 11000 // Note this will need to be adjusted for the friction on the wheels and the voltage
#define MAX_MOTOR_PWM 65000

#define SPEED_RESOLUTION 1000

/// Servo angles
// #define PIVOT_DOWN 173
#define PIVOT_DOWN 150
#define PIVOT_UP 90
#define ARM_CLOSED 90
#define ARM_OPEN 140
#define CLAW_LEVEL_ANGLE 140

/// Can Finding
#define SWEEP_SPEED 80

#define CAN_FINDING_SPEED 160
#define CAN_FAR_DELAY 500
#define CAN_STOP_RANGE 12 // cm

// the threshold where a reading from  the sonar sensor is considered a can
#define CAN_THRESHOLD 150 //cm

// max sure that the timeout for the sonar allows for values at least this big
#define SONAR_MAX_RANGE 170 // cm
// set this based on robot geometry. 5 should be good enough.
#define SONAR_MIN_RANGE 8 // cm

#define FINAL_CAN_TURN_IN_DELAY 50

#endif