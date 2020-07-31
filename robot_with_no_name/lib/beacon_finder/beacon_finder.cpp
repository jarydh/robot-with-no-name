// Used for moving to an IR beacon
// Authors: Thomas

#include "beacon_finder.h"
#include "motors.h"
#include "pinout.h"

#define IR_DEBUG true

#define STOPPING_ERROR 5      //The average error over SAMPLING_SIZE samples to consider the beacon found
#define PICKUP_STRENGTH 60    //The minimum strength at which a signal is considered to be coming from the beacon
#define STOPPING_STRENGTH 300 //The strength at which the beacon is considered found, and the robot is ready to drop the can
#define TIMEOUT 60000         //Milliseconds before giving up on finding the beacon

#define LOCKON_INTERVAL 2000 //milliseconds between locking on to the beacon

#define GAIN 1 / 100
#define P_GAIN 35
#define D_GAIN 19
//#define I_GAIN 1
/*I have not been able to get any kind of improvement from integral gain. 
*If you'd like to add integral gain, you'll have to uncomment various lines,
*and swap the line that calculates speed
*/
#define SAMPLING_SIZE 5 //the number of samples used to determine the derivative_error_sum

bool pointAtBeacon(int angular_speed)
{
    int reading_r = analogRead(IR_RIGHT);
    int reading_l = analogRead(IR_LEFT);

    long last_direction_check_time = millis();

    int strength = reading_l + reading_r;

    if (strength < PICKUP_STRENGTH)
    {
        // start turning towards beacon
        if (reading_r > reading_l)
            turn(angular_speed);
        else
            turn(-angular_speed);
    }

    //rotate until  a signal is picked up, or until timing out
    while (strength < PICKUP_STRENGTH)
    {
        reading_r = analogRead(IR_RIGHT);
        reading_l = analogRead(IR_LEFT);

        strength = reading_l + reading_r;

        if (millis() - last_direction_check_time > TIMEOUT)
        {
            return false;
        }
    }

    // Found the beacon
    stop();

    //begin PID control
    int p = 0;
    int d = 0;
    int derivative_error_list[SAMPLING_SIZE];
    int derivative_error_sum = 0;
    int speed = 0;

    int error = reading_r - reading_l;
    int lastError;

    int num_loops = 0;

    //while(error > STOPPING_ERROR && strength > PICKUP_STRENGTH)
    while (error > STOPPING_ERROR || strength < PICKUP_STRENGTH)
    {
        reading_r = analogRead(IR_RIGHT);
        reading_l = analogRead(IR_LEFT);

        error = reading_r - reading_l;

        strength = reading_r + reading_l;

        p = P_GAIN * error;

        derivative_error_list[0] = (int)error - lastError;

        derivative_error_sum = 0;
        for (int i = SAMPLING_SIZE - 1; i >= 1; i--)
        {
            derivative_error_list[i] = derivative_error_list[i - 1];
            derivative_error_sum += derivative_error_list[i];
        }

        d = D_GAIN * derivative_error_sum / SAMPLING_SIZE;
        lastError = error;

        speed = (int)(p + d) * GAIN;

        // Make sure derivative error list is fully initiallized
        if (num_loops >= SAMPLING_SIZE)
        {
            turn(speed * -1);
        }

        num_loops++;
    }

    stop();

    return true;
}

bool goToBeacon(int speed, int angular_speed)
{
    uint32_t last_direction_check_time = millis();
    int strength;

    // While the robot isn't close to the beacon
    do
    {
        if (millis() - last_direction_check_time > LOCKON_INTERVAL)
        {
            if (!pointAtBeacon(angular_speed))
            {
                return false;
            }

            last_direction_check_time = millis();
        }
        else
        {
            // Drive straight until timeout happens again
            driveStraight(speed);
        }

        strength = analogRead(IR_RIGHT) + analogRead(IR_LEFT);
    } while (strength < STOPPING_STRENGTH);

    stop();

    delay(3000);
    return true;
}