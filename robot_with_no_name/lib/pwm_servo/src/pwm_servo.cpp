// Code for driving servo
// Authors: Jaryd

#include "pwm_servo.h"

#define MIN_PULSE_WIDTH       544     // the shortest pulse sent to a servo
#define MAX_PULSE_WIDTH      2400     // the longest pulse sent to a servo

#define MIN_ANGLE 0
#define MAX_ANGLE 180

const int linearize_slope = (MAX_PULSE_WIDTH - MIN_PULSE_WIDTH) / (MAX_ANGLE - MIN_ANGLE);

void pwmServo::write(int angle)
{
    if (angle < MIN_ANGLE)
        angle = MIN_ANGLE;
    else if (angle > MAX_ANGLE)
        angle = MAX_ANGLE;

    uint16_t time_on = angle * linearize_slope + MIN_PULSE_WIDTH;
    pwm_start(pin, 50, time_on, TimerCompareFormat_t::MICROSEC_COMPARE_FORMAT);
}