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

// Start button
#define START_BUTTON PB12

//motors
#define RIGHT_MOTOR_FORWARD_PIN PA_2
#define RIGHT_MOTOR_BACKWARD_PIN PA_3
#define LEFT_MOTOR_FORWARD_PIN PA_0
#define LEFT_MOTOR_BACKWARD_PIN PA_1

// For some reason, we need to use the int pins otherwise the sonar breaks
#define RIGHT_MOTOR_FORWARD_PIN_INT A0
#define RIGHT_MOTOR_BACKWARD_PIN_INT A1
#define LEFT_MOTOR_FORWARD_PIN_INT A2
#define LEFT_MOTOR_BACKWARD_PIN_INT A3

//beacon finding phototransistors
#define IR_LEFT PA4
#define IR_RIGHT PA5

// Sonar pins
#define SONAR_ECHO_PIN PB9
#define SONAR_TRIGGER_PIN PB8

// Servo pins
#define CLAW_ARMS_SERVO_PIN_INT PB1
#define CLAW_PIVOT_SERVO_PIN_INT PB0

#define CLAW_ARMS_SERVO_PIN PB_1
#define CLAW_PIVOT_SERVO_PIN PB_0

#endif