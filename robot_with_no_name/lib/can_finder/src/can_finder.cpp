// Code for finding cans
// Authors: Jaryd

#include "can_finder.h"

#include "motors.h"
#include "sensor_math.h"

// Sweep constants 
#define SWEEP_ANGLE 180  // angle in degrees to sweep
const int sweep_range_increment = 25;
int sweep_start_range = 50;

// Sonar values
const int num_sonar_readings = NUM_SONAR_READINGS;
#define ECHO_RANGE 10 // Unless right up against a can, anything <10 is an echo
#define CORRECTION_SCALE 2 // Every time the robot moves forward, it goes about 1/3 of a cm

// Driving towards can
const int forwards_speed = 40;
const int reduced_moving_time = 20; // slow down when closer to can
const int reduced_range = 15; // cm
const int stop_range = 10; // cm

// For every 1cm of range, we get 56us of timeout
#define TIMEOUT_TO_RANGE_SLOPE 56

int canFinder::readSonar()
{
    pushNewData(sonar_readings, sonar_ptr.read(), num_sonar_readings);
    return median(sonar_readings, num_sonar_readings);
}

void canFinder::resetSonar()
{
    for(int i = 0; i < num_sonar_readings; i++)
    {
        sonar_readings[i] = sonar_ptr.read();
    }
}

/*
* Takes a sonar object pointer and a range in cm to set the sonar range to.
*/
void canFinder::setSonarRange(int range)
{
    sonar_ptr.setTimeout(range * TIMEOUT_TO_RANGE_SLOPE);
}

/*
* Finds a can, returns true if found, false if not
*/
bool canFinder::findCan()
{
    resetSonar();
    bool is_clockwise = true;
    sweep_range = sweep_start_range;

    while(sweep_range < 500) // Figure out when to stop this
    {
        if(sweep(is_clockwise, sweep_range))
        {
            sweep_start_range = sweep_range; // Set range to start at next time
            return true;
        }
        else
        {
            // Switch directions
            if (is_clockwise)
                is_clockwise = false;
            else
                is_clockwise = true;
            
            // Increment range
            sweep_range += sweep_range_increment;
        }
    }

    return false;
}

// Returns true if it detects something within range and drives towards it, false if it completes the sweep
bool canFinder::sweep(bool is_clockwise, int range)
{
    int moving_time;
    bool found_can = false;
    uint32_t stopped_time;
    int correction = 0;

    // Value between 0 to 1000 for sweeping
    uint16_t sweep_speed = 20; // TODO figure out how to set this
    uint32_t sweep_time = 4000; // TODO figure out how to set this

    setSonarRange(range);
    uint32_t start_time = millis();

    while (millis() - start_time < sweep_time)
    {
        display_ptr.clearDisplay();
        display_ptr.setTextSize(1);
        display_ptr.setTextColor(SSD1306_WHITE);
        display_ptr.setCursor(0,0);

        int sonar_read = readSonar();
        moving_time = 100 - sonar_read / 5;

        // Found can
        if(sonar_read + correction / CORRECTION_SCALE < range - 2 && (found_can || sonar_read > ECHO_RANGE))
        {
            found_can = true;
            stopped_time = 0;
            correction ++;

            // At the can
            if(sonar_read <= stop_range)
            {
                display_ptr.print("Arrived at can!");
                display_ptr.display();
                stop();
                return true;
            }
            // Getting close to the can
            else if(sonar_read <= reduced_range)
            {
                display_ptr.print("Close to can! Read range: ");
                display_ptr.println(sonar_read);
                display_ptr.display();
                moving_time = reduced_moving_time;
                driveStraight(forwards_speed);
                start_time = millis();
            }
            else
            {
                display_ptr.print("Found a can! Read range: ");
                display_ptr.println(sonar_read);
                display_ptr.display();
                driveStraight(forwards_speed);
                start_time = millis();
            }
        }
        // No can
        else
        {
            stopped_time = 50;
            if (is_clockwise)
                turn(sweep_speed);
            else
                turn(sweep_speed * -1);
        }


        delay(moving_time);

        stop();

        delay(stopped_time);

        display_ptr.print("Search range: ");
        display_ptr.println(range);
        display_ptr.display();
    }

    // Did not find can
    return false;
}
