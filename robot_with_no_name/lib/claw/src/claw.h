// Code for controlling the claw
// Authors: Jaryd

#ifndef CLAW_H
#define CLAW_H

#include <Arduino.h>
#include <Adafruit_SSD1306.h>

#include <Servo.h>


class Claw {
    public:
        // Constructor
        Claw(Servo& arm_servo, Servo& pivot_servo, Adafruit_SSD1306& display)
            : arm_servo_ptr(arm_servo), pivot_servo_ptr(pivot_servo), display_ptr(display) {}      
        bool pickUpCan();
        bool dropCan();
    private:
        Servo& arm_servo_ptr;
        Servo& pivot_servo_ptr;
        Adafruit_SSD1306& display_ptr;
};



#endif