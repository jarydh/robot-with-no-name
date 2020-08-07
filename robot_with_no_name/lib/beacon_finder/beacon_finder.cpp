// Used for moving to an IR beacon
// Authors: Thomas, Jaryd

#include "beacon_finder.h"
#include "motors.h"
#include "pinout.h"

#include <Adafruit_SSD1306.h>
#include <math.h>

#define IR_DEBUG 1

// IR values
#define STOPPING_ERROR 30            //The average error over SAMPLING_SIZE samples to consider the beacon found
#define PICKUP_STRENGTH 100          //The minimum strength at which a signal is considered to be coming from the beacon
#define STOPPING_STRENGTH 2000       //The strength at which the beacon is considered found, and the robot is ready to drop the can
#define POINT_AT_BEACON_TIMEOUT 3000 //Milliseconds before giving up on finding the beacon

// PID Sonar values
#define SONAR_FOUND_BIN 10   //cm
#define PING_SONAR_LOOPS 700 // how many loops to do in PID before checking sonar

// PID values
#define GAIN 1 / 20
#define P_GAIN 3
#define D_GAIN 100

#define PID_TIMEOUT_MS 10000  // PID timeout

#define SAMPLING_SIZE 5 //the number of samples used to determine the derivative_error_sum

#define DEFAULT_PID_SPEED 80

// Back away from beacon
#define BACK_AWAY_STRAIGHT_SPEED -150
#define BACK_AWAY_ANGULAR_SPEED 200
#define BACK_AWAY_STRAIGHT_TIME_MS 250
#define BACK_AWAY_ANGULAR_TIME_MS 400


void backAway()
{
    drive(BACK_AWAY_STRAIGHT_SPEED, 0);
    delay(BACK_AWAY_STRAIGHT_TIME_MS);
    drive(0, BACK_AWAY_ANGULAR_SPEED);
    delay(BACK_AWAY_ANGULAR_TIME_MS);
    hard_stop();
}


bool pointAtBeacon(int angular_speed, Adafruit_SSD1306 display)
{
    int reading_r = analogRead(IR_RIGHT);
    int reading_l = analogRead(IR_LEFT);

    uint32_t start_time = millis();

    int strength = reading_l + reading_r;

    if (strength < PICKUP_STRENGTH)
    {
        // start turning towards beacon
        if (reading_r > reading_l)
            drive(0, angular_speed);
        else
            drive(0, -angular_speed);
    }

    //rotate until  a signal is picked up, or until timing out
    while (strength < PICKUP_STRENGTH)
    {
        reading_r = analogRead(IR_RIGHT);
        reading_l = analogRead(IR_LEFT);

        strength = reading_l + reading_r;

        if (millis() - start_time > POINT_AT_BEACON_TIMEOUT)
        {
            if (IR_DEBUG)
            {
                display.clearDisplay();
                display.setCursor(0, 0);
                display.println("FAILED TO FIND BEACON");
                display.display();
            }

            // Drive in a random direction for a bit
            drive(100, 0);
            delay(400);
            stop();
            return false;
        }
    }
    // Found the beacon
    stop();

    return true;
}

bool pidToBeacon(Adafruit_SSD1306 display, sonarWrapper sonar)
{
    uint32_t pid_start_time = millis();
    int reading_r = analogRead(IR_RIGHT);
    int reading_l = analogRead(IR_LEFT);

    if (IR_DEBUG)
    {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("Starting PID...");
        display.display();
    }

    // sonar.setSonarRange(SONAR_FOUND_BIN + 5);
    // sonar.resetSonar();

    //begin PID control
    int p = 0;
    int d = 0;
    int derivative_error_list[SAMPLING_SIZE];
    int derivative_error_sum = 0;
    int speed = 0;

    int sonar_read;

    int error = reading_r - reading_l;
    int lastError = error;
    int strength = reading_r + reading_l;
    int num_loops = 0;
    int ping_sonar_count = 1;

    while (true)
    {
        reading_r = analogRead(IR_RIGHT);
        reading_l = analogRead(IR_LEFT);

        error = reading_r - reading_l;

        strength = reading_r + reading_l;

        p = P_GAIN * error;

        derivative_error_list[0] = error - lastError;

        derivative_error_sum = 0;
        for (int i = SAMPLING_SIZE - 1; i >= 1; i--)
        {
            derivative_error_list[i] = derivative_error_list[i - 1];
            derivative_error_sum += derivative_error_list[i];
        }

        d = D_GAIN * derivative_error_sum / SAMPLING_SIZE;
        lastError = error;

        speed = (int)(p + d) * GAIN;

        // For debugging
        while (digitalRead(START_BUTTON) == LOW)
        {
            stop();
            display.clearDisplay();
            display.setCursor(0, 0);
            display.println("PID");
            display.print("right:");
            display.println(reading_r);
            display.print("left:");
            display.println(reading_l);
            display.print("error:");
            display.println(error);
            display.print("speed:");
            display.println(speed);
            display.display();
            delay(10);
        }

        // Make sure derivative error list is fully initiallized
        if (num_loops >= SAMPLING_SIZE)
        {
            drive(DEFAULT_PID_SPEED, speed);
        }

        // Check
        if(digitalRead(RIGHT_SWITCH) == LOW || digitalRead(LEFT_SWITCH) == LOW || millis() - pid_start_time > PID_TIMEOUT_MS)
        {
            break;
        }

        // if (ping_sonar_count >= PING_SONAR_LOOPS)
        // {
        //     stop();
        //     sonar_read = sonar.readSonar();
        //     display.clearDisplay();
        //     display.setCursor(0, 0);
        //     display.println("Sonar Read:");
        //     display.println(sonar_read);
        //     display.display();
        //     if (sonar_read <= SONAR_FOUND_BIN && abs(error) < STOPPING_ERROR)
        //     {
        //         break;
        //     }
        //     ping_sonar_count = 1;
        // }
        // else
        // {
        //     ping_sonar_count++;
        // }

        num_loops++;
    }

    hard_stop();

    if (IR_DEBUG)
    {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("Done PID!");
        display.print("right:");
        display.println(reading_r);
        display.print("left:");
        display.println(reading_l);
        display.print("error:");
        display.println(error);
        display.print("speed:");
        display.println(speed);
        display.print("sonar:");
        display.println(sonar_read);
        display.display();
    }

    // TODO figure out if PID ever will fail
    return true;
}

void IRDebug(Adafruit_SSD1306 display)
{
    int reading_r, reading_l, strength, error;

    while (true)
    {
        reading_r = analogRead(IR_RIGHT);
        reading_l = analogRead(IR_LEFT);
        error = reading_r - reading_l;
        strength = reading_r + reading_l;

        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("right:");
        display.println(reading_r);
        display.print("left:");
        display.println(reading_l);
        display.print("error:");
        display.println(error);
        display.print("strength:");
        display.println(strength);
        display.display();
    }
}
