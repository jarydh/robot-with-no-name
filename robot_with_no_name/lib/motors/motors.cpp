// Used for controlling motors
// Authors: Jaryd

#include "motors.h"
#include "pinout.h"

#include <math.h>

// For some reason, setting a value of 0 doesn't seem to turn the motors off
#define MOTOR_OFF 1
#define PMWFREQ 2000

// Min and max PWM values
#define MIN_MOTOR_PWM 24000  // Note this will need to be adjusted for the friction on the wheels and the voltage
#define MAX_MOTOR_PWM 65000

#define SPEED_RESOLUTION 1000

// TODO: Linearize this better, since it seems the speeds between 0-100 are a 
//       lot more sensitive than the speeds between 100-1000
int motor_linearize_slope = (MAX_MOTOR_PWM - MIN_MOTOR_PWM) / SPEED_RESOLUTION;

void driveStraight(int speed)
{
    int forwards_speed;
    int backwards_speed;
    
    // Motors off
    if (speed == 0)
    {
        forwards_speed = MOTOR_OFF;
        backwards_speed = MOTOR_OFF;
    }
    // Motors forwards
    else if (speed > 0)
    {
        if (speed > SPEED_RESOLUTION)
        {
            speed = SPEED_RESOLUTION;
        }

        forwards_speed = motor_linearize_slope * speed + MIN_MOTOR_PWM;
        backwards_speed = MOTOR_OFF;
    }
    // Motors backwards
    else if (speed < 0)
    {
        if (speed < -SPEED_RESOLUTION)
        {
            speed = -SPEED_RESOLUTION;
        }

        backwards_speed = motor_linearize_slope * speed * -1 + MIN_MOTOR_PWM;
        forwards_speed = MOTOR_OFF;
    }

    // Set motor speeds
    pwm_start(LEFT_MOTOR_FORWARD_PIN, PMWFREQ, forwards_speed, TICK_COMPARE_FORMAT);
    pwm_start(LEFT_MOTOR_BACKWARD_PIN, PMWFREQ, backwards_speed, TICK_COMPARE_FORMAT);
    pwm_start(RIGHT_MOTOR_FORWARD_PIN, PMWFREQ, forwards_speed, TICK_COMPARE_FORMAT);
    pwm_start(RIGHT_MOTOR_BACKWARD_PIN, PMWFREQ, backwards_speed, TICK_COMPARE_FORMAT);
}

void stop()
{
    driveStraight(0);
}


void turn(int angular_speed)
{
    int left_forward_speed = MOTOR_OFF;
    int left_backward_speed = MOTOR_OFF;
    int right_forward_speed = MOTOR_OFF;
    int right_backward_speed = MOTOR_OFF;
    
    int linearized_speed;

    // Motors off
    if (angular_speed == 0)
    {
        // Do nothing
    }
    // Turning right
    else if (angular_speed > 0)
    {
        if (angular_speed > SPEED_RESOLUTION)
        {
            angular_speed = SPEED_RESOLUTION;
        }

        linearized_speed = motor_linearize_slope * angular_speed + MIN_MOTOR_PWM;
        left_forward_speed = linearized_speed;
        right_backward_speed = linearized_speed;
    }
    // Motors forwards
    else if (angular_speed < 0)
    {
        if (angular_speed < -SPEED_RESOLUTION)
        {
            angular_speed = -SPEED_RESOLUTION;
        }

        linearized_speed = motor_linearize_slope * angular_speed * -1 + MIN_MOTOR_PWM;
        right_forward_speed = linearized_speed;
        left_backward_speed = linearized_speed;
    }

    // Set motor speeds
    pwm_start(LEFT_MOTOR_FORWARD_PIN, PMWFREQ, left_forward_speed, TICK_COMPARE_FORMAT);
    pwm_start(LEFT_MOTOR_BACKWARD_PIN, PMWFREQ, left_backward_speed, TICK_COMPARE_FORMAT);
    pwm_start(RIGHT_MOTOR_FORWARD_PIN, PMWFREQ, right_forward_speed, TICK_COMPARE_FORMAT);
    pwm_start(RIGHT_MOTOR_BACKWARD_PIN, PMWFREQ, right_backward_speed, TICK_COMPARE_FORMAT);
}

void driveMotor(PinName motor_pin, int speed)
{
    if (speed == MOTOR_OFF)
    {
        pwm_start(motor_pin, PMWFREQ, MOTOR_OFF, TICK_COMPARE_FORMAT);
        return;
    }
    int linearized_speed = motor_linearize_slope * speed + MIN_MOTOR_PWM;
    pwm_start(motor_pin, PMWFREQ, linearized_speed, TICK_COMPARE_FORMAT);
}

void setMotorSpeed(motorSides side, int speed)
{    
    if (side == LEFT)
    {
        if(speed > 0)
        {
            driveMotor(LEFT_MOTOR_FORWARD_PIN, speed);
            driveMotor(LEFT_MOTOR_BACKWARD_PIN, MOTOR_OFF);
        }
        else if (speed < 0)
        {
            driveMotor(LEFT_MOTOR_BACKWARD_PIN, speed * -1);
            driveMotor(LEFT_MOTOR_FORWARD_PIN, MOTOR_OFF);
        }
        else
        {
            driveMotor(LEFT_MOTOR_BACKWARD_PIN, MOTOR_OFF);
            driveMotor(LEFT_MOTOR_FORWARD_PIN, MOTOR_OFF);
        }
    }
    else if (side == RIGHT)
    {
        if(speed > 0)
        {
            driveMotor(RIGHT_MOTOR_FORWARD_PIN, speed);
            driveMotor(RIGHT_MOTOR_BACKWARD_PIN, MOTOR_OFF);
        }
        else if (speed < 0)
        {
            driveMotor(RIGHT_MOTOR_BACKWARD_PIN, speed * -1);
        } 
        else
        {
            driveMotor(RIGHT_MOTOR_BACKWARD_PIN, MOTOR_OFF);
            driveMotor(RIGHT_MOTOR_FORWARD_PIN, MOTOR_OFF);
        }
    }
}