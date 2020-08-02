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
#define ECHO_RANGE 10 // Unless right up against a can, anything <10 is an echo
#define CORRECTION_SCALE 2 // Every time the robot moves forward, it goes about 1/3 of a cm

// Driving towards can
#define CAN_FINDING_SPEED 40
#define CAN_ALIGNMENT_SPEED 20 // slow down when closer to can
#define CAN_ALIGNMENT_RANGE 10 // cm
#define CAN_ALIGNMENT_STOP_RANGE 7 // cm

#define MIN_CAN_DETECTION_DIFFERENCE 20 //cm

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
    bool find_can() {
        // make an assumption that we are not pointing at a can
        // TODO: add a minimum range here where the first measurement IS assumed to be a can
        int last_sonar;
        int cur_sonar = read_sonar();

        // start to turn
        drive(0, SWEEP_SPEED);

        // read sonar until a large dip in sonar range is detected
        // TODO: possibly add a timeout to this loop
        do {
            last_sonar = cur_sonar;
            int cur_sonar = read_sonar();
        } while(last_sonar - cur_sonar < MIN_CAN_DETECTION_DIFFERENCE);
        // cur sonar now contains the current distance to the can
        // TODO: need an abort on tape detection and an abort on beacon recognition

        // stop briefly to lose momentum
        stop();
        delay(500);

        // TODO: course correction here
        // placeholder code
        drive(CAN_FINDING_SPEED, 0);
        delay(1000);
        drive(CAN_ALIGNMENT_SPEED, 0);
        delay(500);
        stop();
    };



private:

    /*
        Reads from the sonar sensor multiple times and returns the median value.
    */
    int read_sonar() {
        // TODO: decide on if multiple sonar measurements makes sense
        for(int i = 0; i < NUM_SONAR_READINGS; i++) {
            sonar_readings[i] = sonar.read();
        }

        return median(sonar_readings, NUM_SONAR_READINGS);
    }

    int sonar_readings[NUM_SONAR_READINGS];
    Ultrasonic &sonar;
};

#endif
