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
#define LEFT_MOTOR_FORWARD_PIN PB_6
#define LEFT_MOTOR_BACKWARD_PIN PB_7
#define RIGHT_MOTOR_FORWARD_PIN PB_8
#define RIGHT_MOTOR_BACKWARD_PIN PB_9

// need integer types for Arduino-based libraries
#define LEFT_MOTOR_FORWARD_PIN_INT PB6
#define LEFT_MOTOR_BACKWARD_PIN_INT PB7
#define RIGHT_MOTOR_FORWARD_PIN_INT PB8
#define RIGHT_MOTOR_BACKWARD_PIN_INT PB9

// beacon finding phototransistors
#define IR_LEFT PA4
#define IR_RIGHT PA5

// Sonar pins
#define SONAR_ECHO_PIN PA0
#define SONAR_TRIGGER_PIN PA1

// Servo pins
#define CLAW_ARMS_SERVO_PIN PB1
#define CLAW_PIVOT_SERVO_PIN PB0

// config for robot

/// Motors
// value of 1 for motor off as 0 causes unwanted behaviour
#define MOTOR_OFF 1
// PWM frequency should be as low as possible without causing significant oscillation of the motor's power output
#define PMWFREQ 256

// Min and max PWM values
#define MIN_MOTOR_PWM 24000 // Note this will need to be adjusted for the friction on the wheels and the voltage
#define MAX_MOTOR_PWM 65000

#define SPEED_RESOLUTION 1000

/// Servo angles
#define PIVOT_DOWN 120
#define PIVOT_UP 180
#define ARM_CLOSED 180
#define ARM_OPEN 160

#endif