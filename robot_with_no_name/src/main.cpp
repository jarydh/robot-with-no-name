// External libraries
#include <Servo.h>
#include <Wire.h>
// #include <Adafruit_SSD1306.h>
#include <Ultrasonic.h>

// Internal libraries
// #include "motors.h"
#include "pinout.h"
// #include "beacon_finder.h"
// #include "can_finder.h"
// #include "claw.h"

// Sonar sensor
#define SONAR_TIMEOUT 10000UL  // Time in micro seconds before sonar times out, determines range and how long the ping will block for
Ultrasonic sonar(SONAR_TRIGGER_PIN, SONAR_ECHO_PIN, SONAR_TIMEOUT);
unsigned int sonar_distance;

// Can finder object
// canFinder can_finder(sonar, display);

// Claw
// Servo arm_servo;
// Servo pivot_servo;
// Claw claw(arm_servo, pivot_servo, display);


int sonar_range = 100;  // cm
int sonar_read;

void setup() {
  // IR Pins
  // pinMode(IR_LEFT, INPUT);
  // pinMode(IR_RIGHT, INPUT);

  // Motor pins
  // pinMode(LEFT_MOTOR_FORWARD_PIN_INT, OUTPUT);
  // pinMode(LEFT_MOTOR_BACKWARD_PIN_INT, OUTPUT);
  // pinMode(RIGHT_MOTOR_FORWARD_PIN_INT, OUTPUT);
  // pinMode(RIGHT_MOTOR_BACKWARD_PIN_INT, OUTPUT);

  // Servo pins
  // arm_servo.attach(CLAW_ARMS_SERVO_PIN);
  // pivot_servo.attach(CLAW_PIVOT_SERVO_PIN);

  // display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // display.display();
  // display.clearDisplay();
  // display.setTextSize(1);
  // display.setTextColor(SSD1306_WHITE);
  // display.setCursor(0,0);
  // delay(50);

  // can_finder.findCan();
  // pointAtBeacon(20, display);
  // goToBeacon(20, 20, display);
}


void loop() 
{
};
