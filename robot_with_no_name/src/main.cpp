// External libraries
#include <Wire.h>
#include <Ultrasonic.h>
#include <Adafruit_SSD1306.h>

// Internal libraries
#include "motors.h"
#include "pinout.h"
#include "beacon_finder.h"
#include "can_finder.h"
#include "sonar.h"
#include "claw.h"
#include "pwm_servo.h"

// Display
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // This display does not have a reset pin accessible

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

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
  // Display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);

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

  pinMode(START_BUTTON, INPUT_PULLUP);

  arm_servo.write(ARM_OPEN);
  pivot_servo.write(PIVOT_UP);

  while(digitalRead(START_BUTTON) == HIGH)
  {
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Press button to start...");
    display.display();
  }
  display.clearDisplay();

  can_finder.find_can();
  delay(100);
  drive(100, 0);
  delay(50);
  hard_stop();
  claw.pickUpCan();

  // while(pointAtBeacon(20, display)){}

  // pidToBeacon(display, sonar_wrapper);
  // claw.dropCan();
}

void loop()
{};
