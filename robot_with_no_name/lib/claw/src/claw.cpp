// Code for controlling the claw
// Authors: Jaryd

#include "claw.h"

#include <Arduino.h>
#include "pwm_servo.h"

#include "pinout.h"

bool Claw::pickUpCan()
{
    arm_servo_ptr.write(ARM_OPEN);
    pivot_servo_ptr.write(PIVOT_DOWN);
    delay(1000);
    arm_servo_ptr.write(ARM_CLOSED);
    delay(1000);
    pivot_servo_ptr.write(PIVOT_UP);

    // TODO use IR sensor to determine if picked up successfully
    return true;
}

bool Claw::dropCan()
{

    pivot_servo_ptr.write(PIVOT_UP);
    delay(1000);
    arm_servo_ptr.write(ARM_OPEN);

    // TODO use IR sensor to determine if picked up successfully
    return true;
}
