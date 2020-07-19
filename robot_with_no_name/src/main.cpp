// External libraries
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

// Internal libraries
#include "motors.h"
#include "pinout.h"
#include "beacon_finder.h"

//operating modes
#define SETUP_DISPLAY true


// Display
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 	-1 // This display does not have a reset pin accessible

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {

  pinMode(LEFT_MOTOR_FORWARD_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_BACKWARD_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_FORWARD_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_BACKWARD_PIN, OUTPUT);

  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  // Displays Adafruit logo by default. call clearDisplay immediately if you don't want this.
  display.display();
    delay(5000);
}


void loop() 
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  
  // display.println("hello world");
  // display.display();
  
  // driveStraight(100);
  // delay(2000);
  // driveStraight(-100);
  // delay(2000);
  // driveStraight(0);

  pointAtBeacon(20,display);
  //goToBeacon(100,20,display);

  //pointAtBeacon(20, display);
  //goToBeacon(500,500);

  // delay(20000);
};