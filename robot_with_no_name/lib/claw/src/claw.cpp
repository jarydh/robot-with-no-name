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
    delay(500);
    arm_servo_ptr.write(ARM_CLOSED);
    delay(500);
    pivot_servo_ptr.write(PIVOT_UP);

    return true;
}

bool Claw::dropCan()
{

    pivot_servo_ptr.write(PIVOT_UP);
    delay(500);
    arm_servo_ptr.write(ARM_OPEN);

    return true;
}
