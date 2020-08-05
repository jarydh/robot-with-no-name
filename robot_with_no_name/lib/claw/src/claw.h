// Code for controlling the claw
// Authors: Jaryd

#ifndef CLAW_H
#define CLAW_H

#include <Arduino.h>
#include "pwm_servo.h"

#include "pinout.h"

class Claw
{
public:
    Claw(pwmServo &arm_servo, pwmServo &pivot_servo)
        : arm_servo_ptr(arm_servo), pivot_servo_ptr(pivot_servo) {}
    bool pickUpCan();
    bool dropCan();

private:
    pwmServo &arm_servo_ptr;
    pwmServo &pivot_servo_ptr;
};

#endif