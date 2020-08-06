// Code for finding cans
// Authors: Jaryd

#include "can_finder.h"

#include <Arduino.h>
#include <Ultrasonic.h>
#include <math.h>

#include "motors.h"
#include "beacon_finder.h"
#include "pinout.h"

#define FILTER_WEIGHT 87 // Value between 0 and 100, higher means more sensitive but less filtered

#define LOST_CAN_MS 500 // After this time, resets threshold
#define SPEED_REDUCTION_DISTANCE 55
#define SPEED_REDUCTION_DELAY_TIME_MS 25
#define SPEED_CLOSE_REDUCTION_DISTANCE 25
#define SPEED_CLOSE_REDUCTION_DELAY_TIME_MS 45
#define SPEED_REDUCTION 100 // percent speed to drive when close

#define CHECK_CAN_THRESHOLD 3 // Difference in sonar to say we picked up a can

#define CAN_FAR_THRESHOLD 95

#define CAN_FINDER_TIMEOUT_MS 15000

bool CanFinder::find_can()
{
    int can_find_start_time = millis();
    drive(0, SWEEP_SPEED);
    int last_saw_can_time = millis();
    int cur_sonar;
    last_sonar = sonar.read();
    int threshold = CAN_THRESHOLD;
    int speed_factor = 100;
do
    {
        // Check if it ran into the wall or the bin
        if(digitalRead(RIGHT_SWITCH) == LOW || digitalRead(LEFT_SWITCH) == LOW)
        {
            backAway();
        }     
        // Check for timeout
        else if (millis() - can_find_start_time > CAN_FINDER_TIMEOUT_MS)  
        {   
            stop();
            return false;
        }

        cur_sonar = read_sonar();

        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("Reading: ");
        display.println(cur_sonar);
        display.display();

        if (cur_sonar > threshold)
        {
            hard_stop();
            delay(100);

            while (cur_sonar > threshold)
            {
                // Check if it ran into the wall or the bin
                if(digitalRead(RIGHT_SWITCH) == LOW || digitalRead(LEFT_SWITCH) == LOW)
                {
                    backAway();
                }     
                // Check for timeout
                else if (millis() - can_find_start_time > CAN_FINDER_TIMEOUT_MS)  
                {
                    stop();
                    return false;
                }


                if(millis() - last_saw_can_time > LOST_CAN_MS)
                {
                    threshold = CAN_THRESHOLD;
                }
                drive(0, SWEEP_SPEED);
                delay(100);
                stop();
                delay(100);
                cur_sonar = read_sonar();
                display.clearDisplay();
                display.setCursor(0, 0);
                display.print("Reading: ");
                display.println(cur_sonar);
                display.print("Threshold: ");
                display.println(threshold);
                display.display();
            };
        }
        else
        {
            if (cur_sonar > 30)
            {
                threshold = cur_sonar + 10;
                last_saw_can_time = millis();
                speed_factor = 100;
            }
            if (cur_sonar < SPEED_CLOSE_REDUCTION_DISTANCE)
            {
                stop();
                delay(SPEED_CLOSE_REDUCTION_DELAY_TIME_MS);
                speed_factor = SPEED_REDUCTION;
            }
            else if (cur_sonar < SPEED_REDUCTION_DISTANCE)
            {
                stop();
                delay(SPEED_REDUCTION_DELAY_TIME_MS);
                speed_factor = SPEED_REDUCTION;
            }
            

            // GAS, GAS, GAS
            drive(CAN_FINDING_SPEED * speed_factor / 100, 0);
            if (threshold > CAN_FAR_THRESHOLD)
            {
                delay(CAN_FAR_DELAY);
            }
        }
    } while (cur_sonar > CAN_STOP_RANGE);

    hard_stop();
    delay(100);

    drive(-100, 0);
    delay(50);
    stop();
    delay(50);

    // turn towards can
    drive(0, SWEEP_SPEED);
    delay(FINAL_CAN_TURN_IN_DELAY);
    stop();
    delay(50);

    // drive towards can
    drive(CAN_FINDING_SPEED, 0);
    delay(FINAL_CAN_STRAIGHT_IN_DELAY);
    stop();
    delay(50);

    return true;
}


int CanFinder::read_sonar()
{
    int read = sonar.read();
    while (read < SONAR_MIN_RANGE && read > SONAR_MAX_RANGE)
    {
        read = sonar.read();
    }

    int out = (read * FILTER_WEIGHT + last_sonar * (100 - FILTER_WEIGHT)) / 100;
    last_sonar = out;
    return out;
}

bool CanFinder::check_can()
{
    return true;
    int last = last_sonar;
    int current = read_sonar();
    return abs(last - current) > CHECK_CAN_THRESHOLD;
}
