// Code for finding cans
// Authors: Jaryd

#ifndef CAN_FINDER_H
#define CAN_FINDER_H

#include <Arduino.h>
#include <Ultrasonic.h>

#include "motors.h"

// For every 1cm of range, we get 56us of timeout
#define TIMEOUT_TO_RANGE_SLOPE 56

// TODO: move this to pinout.h?
#define NUM_SONAR_READINGS 3

// Sweep constants
#define SWEEP_SPEED 25

// Sonar values
#define ECHO_RANGE 10      // Unless right up against a can, anything <10 is an echo
#define CORRECTION_SCALE 2 // Every time the robot moves forward, it goes about 1/3 of a cm

// Driving towards can
#define CAN_FINDING_SPEED 40
#define CAN_ALIGNMENT_STOP_RANGE 14 // cm

class CanFinder
{
public:
    // Constructor
    CanFinder(Ultrasonic &sonar)
        : sonar(sonar) {}

    /*
        can-finding algorithm:
            turn in place until a can is 'detected' by sonar
                if not detected, cry I guess
            move towards can while adjusting course
                use PID (probably actually PD) or something else for this step
            once close to can, move slowly and line up to claw
            stop
    */
    bool find_can()
    {
        // make an assumption that we are not pointing at a can
        // TODO: add a minimum range here where the first measurement IS assumed to be a can
        int cur_sonar;
        int threshold = 75;

        // read sonar until a large dip in sonar range is detected
        // TODO: possibly add a timeout to this loop
        while ((cur_sonar = read_sonar()) > CAN_ALIGNMENT_STOP_RANGE)
        {
            if (cur_sonar > threshold)
            {
                stop();
                delay(100);
                while (cur_sonar > threshold)
                {
                    // TODO: optimize this or something
                    // start to turn
                    drive(0, SWEEP_SPEED);
                    delay(100);
                    stop();
                    delay(100);
                    cur_sonar = read_sonar();
                };

                // turn juuust a lil bit extra
                drive(0, SWEEP_SPEED);
                delay(200);
                stop();
                delay(100);
            }

            // GAS, GAS, GAS
            drive(CAN_FINDING_SPEED, 0);

            // TODO: need an abort on tape detection and an abort on beacon recognition
            // TODO: adjust this
            // if (threshold > 30)
            // {
            //     delay(threshold * 300 / CAN_FINDING_SPEED);
            // }
            // else
            // {
            //     delay(100);
            // }
            threshold = cur_sonar + 5;
        };

        stop();
        return true;
    };

private:
    /*
        Reads from the sonar sensor multiple times and returns the median value.
    */
    int read_sonar()
    {
        // TODO: decide on if multiple sonar measurements makes sense
        // for (int i = 0; i < NUM_SONAR_READINGS; i++)
        // {
        //     sonar_readings[i] = sonar.read();
        // }

        // TODO: filter for readings that echo off of the claw
        // return median(sonar_readings, NUM_SONAR_READINGS);
        int out = sonar.read();
        while (out < 5 && out > 150)
        {
            out = sonar.read();
        }

        return out;
    }

    /*
        Realigns to can. Assumes that the can is within a small angle to the robot.

        Algorithm:
            oscillate back and forth with increasing speed until the can is found.
            mostly just cry
    */
    void realign_to_can(int can_distance, int forwards_speed)
    {
        int turn_speed = 20;

        while (read_sonar() > can_distance)
        {
            // TODO: same as above but for the additive term
            if (turn_speed > 0)
            {
                turn_speed = -(turn_speed + 5);
            }
            else
            {
                turn_speed = -turn_speed;
            }
            drive(forwards_speed, turn_speed);
            // TODO: tune this delay (should this be a constant?)
            delay(200);
            stop();
            delay(200);
        };
    };

    Ultrasonic &sonar;
};

#endif
