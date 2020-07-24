// Code for controlling the claw
// Authors: Jaryd

#include "claw.h"

#define CLAW_DEBUG 0

bool Claw::pickUpCan()
{
    arm_servo_ptr.write(ARM_OPEN);
    delay(500);
    pivot_servo_ptr.write(PIVOT_DOWN);
    delay(500);
    arm_servo_ptr.write(ARM_CLOSED);
    delay(500);
    pivot_servo_ptr.write(PIVOT_UP);

    if (CLAW_DEBUG)
    {
        display_ptr.clearDisplay();
        display_ptr.setCursor(0,0);
        display_ptr.println("Picked up can");
        display_ptr.display();
    }
    
    return true;
}

bool Claw::dropCan()
{
    pivot_servo_ptr.write(PIVOT_UP);
    delay(1000);
    arm_servo_ptr.write(ARM_OPEN);

    if (CLAW_DEBUG)
    {
        display_ptr.clearDisplay();
        display_ptr.setCursor(0,0);
        display_ptr.println("Dropped can");
        display_ptr.display();
    }
    
    return true;
}