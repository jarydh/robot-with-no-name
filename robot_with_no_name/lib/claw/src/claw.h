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
    bool pickUpCan()
    {
        arm_servo_ptr.write(ARM_OPEN);
        pivot_servo_ptr.write(PIVOT_DOWN);
        delay(1000);
        arm_servo_ptr.write(ARM_CLOSED);
        delay(1000);
        pivot_servo_ptr.write(PIVOT_UP);

        // TODO use IR sensor to determine if picked up successfully
        return true;
    };
    bool dropCan()
    {

        pivot_servo_ptr.write(PIVOT_UP);
        delay(1000);
        arm_servo_ptr.write(ARM_OPEN);

        // TODO use IR sensor to determine if picked up successfully
        return true;
    };

private:
    pwmServo &arm_servo_ptr;
    pwmServo &pivot_servo_ptr;
};

#endif