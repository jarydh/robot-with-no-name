// Code for controlling the claw
// Authors: Jaryd

#include "claw.h"

#define CLAW_DEBUG 0

// Servo angles
#define PIVOT_DOWN 120
#define PIVOT_UP 180
#define ARM_CLOSED 180
#define ARM_OPEN 160

bool Claw::pickUpCan()
{
    arm_servo_ptr.write(ARM_OPEN);
    pivot_servo_ptr.write(PIVOT_DOWN);
    delay(1000);
    arm_servo_ptr.write(ARM_CLOSED);
    pivot_servo_ptr.write(PIVOT_UP);

    if (CLAW_DEBUG)
    {
        display_ptr.clearDisplay();
        display_ptr.setCursor(0,0);
        display_ptr.println("Picked up can");
        display_ptr.display();
    }
    
    // TODO use IR sensor to determine if picked up successfully
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
    
    // TODO use IR sensor to determine if picked up successfully
    return true;
}