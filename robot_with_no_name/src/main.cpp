// External libraries
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#include <Wire.h>

// Internal libraries

// Display
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 	-1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // display.display();
  // delay(2000);


}


void loop() 
{

};