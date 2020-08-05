// External libraries
#include <Wire.h>
#include <Ultrasonic.h>

// Internal libraries
#include "motors.h"
#include "pinout.h"
#include "beacon_finder.h"
#include "can_finder.h"
#include "sonar.h"
#include "claw.h"
#include "pwm_servo.h"

// Sonar sensor
#define SONAR_TIMEOUT 10000UL // Time in micro seconds before sonar times out, determines range and how long the ping will block for
Ultrasonic sonar(SONAR_TRIGGER_PIN, SONAR_ECHO_PIN, SONAR_TIMEOUT);

// Sonar wrapper object for PID
sonarWrapper sonar_wrapper(sonar, display);

// Can finder object
CanFinder can_finder(sonar);

// Claw
pwmServo arm_servo(CLAW_ARMS_SERVO_PIN);
pwmServo pivot_servo(CLAW_PIVOT_SERVO_PIN);
Claw claw(arm_servo, pivot_servo);

void setup()
{
  // IR Pins
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);

  // Motor pins
  pinMode(LEFT_MOTOR_FORWARD_PIN_INT, OUTPUT);
  pinMode(LEFT_MOTOR_BACKWARD_PIN_INT, OUTPUT);
  pinMode(RIGHT_MOTOR_FORWARD_PIN_INT, OUTPUT);
  pinMode(RIGHT_MOTOR_BACKWARD_PIN_INT, OUTPUT);

  // Servo pins
  pinMode(CLAW_PIVOT_SERVO_PIN_INT, OUTPUT);
  pinMode(CLAW_ARMS_SERVO_PIN_INT, OUTPUT);

  claw.dropCan();
  delay(1000);
  pivot_servo.write(CLAW_LEVEL_ANGLE);
  can_finder.find_can();

  delay(1000);
  claw.pickUpCan();
  delay(5000);
  claw.dropCan();
}

void loop(){};
