// External libraries
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

// Internal libraries
#include "motors.h"
#include "pinout.h"
#include "beacon_finder.h"
#include "can_finder.h"

//operating modes
#define SETUP_DISPLAY true

#include <Ultrasonic.h>

// Display
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 	-1 // This display does not have a reset pin accessible

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Sonar sensor
#define SONAR_TIMEOUT 10000UL  // Time in micro seconds before sonar times out, determines range and how long the ping will block for
Ultrasonic sonar(SONAR_TRIGGER_PIN, SONAR_ECHO_PIN, SONAR_TIMEOUT);
unsigned int sonar_distance;

// Can finder object
canFinder can_finder(sonar, display);

int sonar_range = 100;  // cm
int sonar_read;

void setup() {
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);

  pinMode(LEFT_MOTOR_FORWARD_PIN_INT, OUTPUT);
  pinMode(LEFT_MOTOR_BACKWARD_PIN_INT, OUTPUT);
  pinMode(RIGHT_MOTOR_FORWARD_PIN_INT, OUTPUT);
  pinMode(RIGHT_MOTOR_BACKWARD_PIN_INT, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  delay(50);
  // can_finder.findCan();
  // pointAtBeacon(20, display);
  goToBeacon(20, 20, display);
}


void loop() 
{
  // display.println("hello world");
  // display.display();
  
  //goToBeacon(100,20,display);


  // delay(20000);
};
