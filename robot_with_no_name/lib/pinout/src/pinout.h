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
#define LEFT_MOTOR_FORWARD_PIN PA_0
#define LEFT_MOTOR_BACKWARD_PIN PA_1
#define RIGHT_MOTOR_FORWARD_PIN PA_2
#define RIGHT_MOTOR_BACKWARD_PIN PA_3

// need integer types for Arduino-based libraries
#define LEFT_MOTOR_FORWARD_PIN_INT PA0
#define LEFT_MOTOR_BACKWARD_PIN_INT PA1
#define RIGHT_MOTOR_FORWARD_PIN_INT PA2
#define RIGHT_MOTOR_BACKWARD_PIN_INT PA3

// beacon finding phototransistors
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

#define START_BUTTON PB12

// config for robot

/// Motors
// value of 1 for motor off as 0 causes unwanted behaviour
#define MOTOR_OFF 1
// PWM frequency should be as low as possible without causing significant oscillation of the motor's power output
#define PMWFREQ 256

// positive values make it turn more right, negative more left. Adjust until movement is straight.
// note that large values may cause odd behaviour at very low speeds.
#define MOTOR_OFFSET 0

// Min and max PWM values
#define MIN_MOTOR_PWM 24000 // Note this will need to be adjusted for the friction on the wheels and the voltage
#define MAX_MOTOR_PWM 65000

#define SPEED_RESOLUTION 1000

/// Servo angles
#define PIVOT_DOWN 135
#define PIVOT_UP 180
#define ARM_CLOSED 165
#define ARM_OPEN 120
#define CLAW_LEVEL_ANGLE 180

/// Can Finding
#define SWEEP_SPEED 80

#define CAN_FINDING_SPEED 100
#define CAN_FAR_DELAY 250
#define CAN_STOP_RANGE 15 // cm

// the threshold where a reading from  the sonar sensor is considered a can
#define CAN_THRESHOLD 150 //cm

// max sure that the timeout for the sonar allows for values at least this big
#define SONAR_MAX_RANGE 170 // cm
// set this based on robot geometry. 5 should be good enough.
#define SONAR_MIN_RANGE 8 // cm

#define FINAL_CAN_TURN_IN_DELAY 100

#endif