// Code for finding cans
// Authors: Jaryd

#include "can_finder.h"

#include <Arduino.h>
#include <Ultrasonic.h>

#include "motors.h"
#include "pinout.h"

bool CanFinder::find_can()
{
    int cur_sonar;
    int threshold = CAN_THRESHOLD;

    // TODO: possibly add a timeout to this loop
    while ((cur_sonar = read_sonar()) > CAN_STOP_RANGE)
    {
        if (cur_sonar > threshold)
        {
            hard_stop();
            delay(100);

            while (cur_sonar > threshold)
            {
                drive(0, SWEEP_SPEED);
                delay(100);
                stop();
                delay(100);
                cur_sonar = read_sonar();
            };
        }
        // TODO: need an abort on tape detection and an abort on beacon recognition

        if (cur_sonar > 30)
        {
            threshold = cur_sonar + 10;
        }

        // GAS, GAS, GAS
        drive(CAN_FINDING_SPEED, 0);
        if (threshold > 60)
        {
            delay(CAN_FAR_DELAY);
        }
    };

    hard_stop();
    delay(100);

    // turn towards can
    drive(0, SWEEP_SPEED);
    delay(FINAL_CAN_TURN_IN_DELAY);
    stop();
    delay(100);

    return true;
}


int CanFinder::read_sonar()
{
    int out = sonar.read();
    while (out < SONAR_MIN_RANGE && out > SONAR_MAX_RANGE)
    {
        out = sonar.read();
    }

    return out;
}
