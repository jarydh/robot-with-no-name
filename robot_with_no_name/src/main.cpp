#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 	-1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define OBJECT_SENSOR PA0
#define SERVO_PIN PB9

#define LEFT_MOTOR_FORWARDS PA_0
#define LEFT_MOTOR_BACKWARDS PA_1
#define RIGHT_MOTOR_FORWARDS PA_2
#define RIGHT_MOTOR_BACKWARDS PA_3

#define MOTOR_OFF 1

#define PMWFREQ 2000

int pot_read_in;
int motor_speed;
String motor_description = "";
int angle = 0;
bool up = true;

Servo servo;

void setServo(int angle)
{
  servo.write(angle);
}

void turn(int pot_val)
{
    pot_val = pot_val - 511;

    pwm_start(LEFT_MOTOR_FORWARDS, PMWFREQ, pot_val * 75, TICK_COMPARE_FORMAT);
    pwm_start(LEFT_MOTOR_BACKWARDS, PMWFREQ, MOTOR_OFF, TICK_COMPARE_FORMAT);
    pwm_start(RIGHT_MOTOR_BACKWARDS, PMWFREQ, pot_val * 75, TICK_COMPARE_FORMAT);
    pwm_start(RIGHT_MOTOR_FORWARDS, PMWFREQ, MOTOR_OFF, TICK_COMPARE_FORMAT);
}

void setMotorSpeed(int pot_val)
{
  pot_val = pot_val - 511;
  // Motor A is on, motor B is off
  if (pot_val > 0)
  {
    pwm_start(LEFT_MOTOR_FORWARDS, PMWFREQ, pot_val * 75, TICK_COMPARE_FORMAT);
    pwm_start(LEFT_MOTOR_BACKWARDS, PMWFREQ, MOTOR_OFF, TICK_COMPARE_FORMAT);
    pwm_start(RIGHT_MOTOR_FORWARDS, PMWFREQ, pot_val * 75, TICK_COMPARE_FORMAT);
    pwm_start(RIGHT_MOTOR_BACKWARDS, PMWFREQ, MOTOR_OFF, TICK_COMPARE_FORMAT);
    motor_description = "Forward";
    motor_speed = pot_val;
  }
  else if (pot_val < 0)
  {
    pwm_start(LEFT_MOTOR_FORWARDS, PMWFREQ, MOTOR_OFF, TICK_COMPARE_FORMAT);
    pwm_start(LEFT_MOTOR_BACKWARDS, PMWFREQ, pot_val * -75, TICK_COMPARE_FORMAT);
    pwm_start(RIGHT_MOTOR_FORWARDS, PMWFREQ, MOTOR_OFF, TICK_COMPARE_FORMAT);
    pwm_start(RIGHT_MOTOR_BACKWARDS, PMWFREQ, pot_val * -75, TICK_COMPARE_FORMAT);
    motor_description = "Backwards";
    motor_speed = pot_val * -1;
  }
  else
  {
    pwm_start(LEFT_MOTOR_FORWARDS, PMWFREQ, MOTOR_OFF, TICK_COMPARE_FORMAT);
    pwm_start(LEFT_MOTOR_BACKWARDS, PMWFREQ, MOTOR_OFF, TICK_COMPARE_FORMAT);
    motor_description = "None";
    motor_speed = 0;
  }
}

void setup() {
  // display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // servo.attach(SERVO_PIN);

  // // Displays Adafruit logo by default. call clearDisplay immediately if you don't want this.
  // display.display();
  // delay(2000);

  pinMode(LEFT_MOTOR_FORWARDS, OUTPUT);
  pinMode(LEFT_MOTOR_BACKWARDS, OUTPUT);
  pinMode(RIGHT_MOTOR_FORWARDS, OUTPUT);
  pinMode(RIGHT_MOTOR_BACKWARDS, OUTPUT);
}


void loop() {

  turn(150);
  delay(2000);
  turn(900);
  delay(2000);
  // setMotorSpeed(812);
  // delay(500);
  // setMotorSpeed(912);
  // delay(500);
  // setMotorSpeed(812);
  // delay(500);
  // setMotorSpeed(212);
  // delay(500);  
  // setMotorSpeed(112);
  // delay(500);
  // setMotorSpeed(212);
  // delay(500);  

};