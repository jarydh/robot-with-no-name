// Code for controlling the claw
// Authors: Jaryd

#ifndef CLAW_H
#define CLAW_H

#include <Arduino.h>
#include <Adafruit_SSD1306.h>

#include "pwm_servo.h"

// Servo angles
#define PIVOT_DOWN 135
#define PIVOT_UP 180
#define ARM_CLOSED 165
#define ARM_OPEN 120

class Claw {
    public:
        // Constructor
        Claw(pwmServo& arm_servo, pwmServo& pivot_servo, Adafruit_SSD1306& display)
            : arm_servo_ptr(arm_servo), pivot_servo_ptr(pivot_servo), display_ptr(display) {}      
        bool pickUpCan();
        bool dropCan();
    private:
        pwmServo& arm_servo_ptr;
        pwmServo& pivot_servo_ptr;
        Adafruit_SSD1306& display_ptr;
};



#endif