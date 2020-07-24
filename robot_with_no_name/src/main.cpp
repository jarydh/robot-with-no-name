// External libraries
#include <Wire.h>
#include <Ultrasonic.h>

// Internal libraries
#include "motors.h"
#include "pinout.h"
#include "beacon_finder.h"
#include "can_finder.h"
#include "claw.h"
#include "pwm_servo.h"

// Sonar sensor
#define SONAR_TIMEOUT 10000UL // Time in micro seconds before sonar times out, determines range and how long the ping will block for
Ultrasonic sonar(SONAR_TRIGGER_PIN, SONAR_ECHO_PIN, SONAR_TIMEOUT);

// Can finder object
CanFinder can_finder(sonar);

// Claw
Servo arm_servo;
Servo pivot_servo;
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

<<<<<<< HEAD
  == == == =
               display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  arm_servo.write(ARM_OPEN);
  pivot_servo.write(PIVOT_UP);

  while (digitalRead(START_BUTTON) == HIGH)
  {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Press button to start...");
    display.display();
  }
>>>>>>> 0d19054... added pwm servo library
  // can_finder.findCan();
  // pointAtBeacon(20);
  // goToBeacon(20, 20);
}

void loop(){
    // 2 primary loops: finding can, and finding bin
};

// can-finding loop
void find_can()
{
<<<<<<< HEAD
}

// finding bin loop
void find_bin(){} == == == =

                               can_finder.findCan();

claw.pickUpCan();
delay(3000);

claw.dropCan();
delay(10000);
}
;
>>>>>>> 0d19054... added pwm servo library
