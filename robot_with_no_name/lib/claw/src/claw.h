// Code for controlling the claw
// Authors: Jaryd

#ifndef CLAW_H
#define CLAW_H

#include <Arduino.h>
#include <Servo.h>

#include "pinout.h"

class Claw
{
public:
    Claw(Servo &arm_servo, Servo &pivot_servo)
        : arm_servo_ptr(arm_servo), pivot_servo_ptr(pivot_servo) {}
    bool pickUpCan()
    {
        arm_servo_ptr.write(ARM_OPEN);
        pivot_servo_ptr.write(PIVOT_DOWN);
        delay(1000);
        arm_servo_ptr.write(ARM_CLOSED);
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
    Servo &arm_servo_ptr;
    Servo &pivot_servo_ptr;
};

#endif