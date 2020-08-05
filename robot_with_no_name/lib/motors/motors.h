// Used for controlling motors
// Authors: Jaryd

#ifndef MOTORS_H
#define MOTORS_H

// External Libraries
#include <Wire.h>
#include <pinout.h>

#include "sensor_math.h"

#define HARD_STOP_IMPULSE_DIVISOR 10

// TODO: this should be made either logarithmic or piecewise to better fit motor power vs torque
int motor_linearize_slope = (MAX_MOTOR_PWM - MIN_MOTOR_PWM) / SPEED_RESOLUTION;

int last_speed = 0;
int last_angular_speed = 0;

int last_drive_time = millis();

/*
* Sets motor speed based on both speed and angular_speed, where speed increases power to both motors in the same direction,
* and angular_speed increases it in opposite directions, where positive values are clockwise.
*
* Inputs:
*       speed: a value between -SPEED_RESOLUTION (backwards max) and SPEED_RESOLUTION (forwards max).
*       angular_speed: a value between -SPEED_RESOLUTION (left turn max) and SPEED_RESOLUTION (right turn max).
*/
void drive(int speed, int angular_speed)
{
    // we store the last-used speeds so that we don't constantly restart PWM
    if (speed == last_speed && angular_speed == last_angular_speed)
    {
        // don't do anything
        return;
    }
    else
    {
        last_speed = speed;
        last_angular_speed = angular_speed;
        last_drive_time = millis();
    }

    int speed_left = clamp(speed + angular_speed, SPEED_RESOLUTION, -SPEED_RESOLUTION);
    int speed_right = clamp(speed - angular_speed, SPEED_RESOLUTION, -SPEED_RESOLUTION);

    int speed_left_f = MOTOR_OFF;
    int speed_left_b = MOTOR_OFF;
    int speed_right_f = MOTOR_OFF;
    int speed_right_b = MOTOR_OFF;

    if (speed_left < 0)
    {
        speed_left_b = motor_linearize_slope * -speed_left + MOTOR_OFFSET + MIN_MOTOR_PWM;
    }
    else if (speed_left > 0)
    {
        speed_left_f = motor_linearize_slope * speed_left + MOTOR_OFFSET + MIN_MOTOR_PWM;
    }

    if (speed_right < 0)
    {
        speed_right_b = motor_linearize_slope * -speed_right + MIN_MOTOR_PWM;
    }
    else if (speed_right > 0)
    {
        speed_right_f = motor_linearize_slope * speed_right + MIN_MOTOR_PWM;
    }

    // Set motor speeds
    pwm_start(LEFT_MOTOR_FORWARD_PIN, PMWFREQ, speed_left_f, TICK_COMPARE_FORMAT);
    pwm_start(LEFT_MOTOR_BACKWARD_PIN, PMWFREQ, speed_left_b, TICK_COMPARE_FORMAT);
    pwm_start(RIGHT_MOTOR_FORWARD_PIN, PMWFREQ, speed_right_f, TICK_COMPARE_FORMAT);
    pwm_start(RIGHT_MOTOR_BACKWARD_PIN, PMWFREQ, speed_right_b, TICK_COMPARE_FORMAT);
};

/*
* Turns both motors off
*/
void stop()
{
    drive(0, 0);
};

[[deprecated("Replaced by drive()")]] void driveStraight(int speed)
{
    drive(speed, 0);
};

[[deprecated("Replaced by drive()")]] void turn(int angular_speed)
{
    drive(0, angular_speed);
};

/*
* Delivers a quick impulse in the opposite direction to quickly stop the robot
* speed and angular_speed should be the last speed commands issued.
*/
void hard_stop()
{
    int drive_time = millis() - last_drive_time;
    if (drive_time > 100)
    {
        drive(-last_speed, -last_angular_speed);
        delay(drive_time / HARD_STOP_IMPULSE_DIVISOR);
    }

    stop();
}

#endif
