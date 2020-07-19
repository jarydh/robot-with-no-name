// Used for moving to an IR beacon
// Authors: Thomas

#include "beacon_finder.h"
#include "motors.h"
#include "pinout.h"

#include <Adafruit_SSD1306.h>

#define IR_DEBUG 1

#define STOP 0

#define STOPPING_ERROR 20 //The average error over SAMPLING_SIZE samples to consider the beacon found
#define PICKUP_STRENGTH 200 //The minimum strength at which a signal is considered to be coming from the beacon
#define STOPPING_STRENGTH 700 //The strength at which the beacon is considered found, and the robot is ready to drop the can
#define TIMEOUT 100000 //Milliseconds before giving up on finding the beacon

#define LOCKON_INTERVAL 2000 //milliseconds between  locking on to the beacon

#define GAIN 1/100
#define P_GAIN 35
#define D_GAIN 19
//#define I_GAIN 1
/*I have not been able to get any kind of improvement from integral gain. 
*If you'd like to add integral gain, you'll have to uncomment various lines,
*and swap the line that calculates speed
*/
#define SAMPLING_SIZE 10 //the number of samples used to determine the slope 

bool pointAtBeacon(int angular_speed, Adafruit_SSD1306 display){
    long starting_time = millis();
    
    if (analogRead(IR_RIGHT) > analogRead(IR_LEFT)) turn(angular_speed);
    else turn(-angular_speed); 

    int strength = 0;
    //rotate until  a signal is picked up, or until timing out
    while(strength < PICKUP_STRENGTH){

        if(IR_DEBUG){
            display.clearDisplay();
            display.setCursor(0,0);
            display.println("finding beacon");
            display.print("L: ");
            display.println(analogRead(IR_LEFT));
            display.print("R: ");
            display.println(analogRead(IR_RIGHT));
            display.print("strength");
            display.print(strength);
            display.print("/");
            display.println(PICKUP_STRENGTH);
            display.display();
            delay(1000);
        }


        strength = analogRead(IR_LEFT) + analogRead(IR_RIGHT);
        if (millis() - starting_time > TIMEOUT){
            if(IR_DEBUG){
                display.clearDisplay();
                display.println("FAILED TO FIND BEACON");
                display.display();
                delay(1000);
            }
        return false;
        }
        
    }

    turn(0);

   if(IR_DEBUG){

        display.println("BEACON FOUND!!!");
        display.display();
        delay(1000);
    }

    //begin PID control
    int p = 0;
    //int i = 0;
    int d = 0;
    int errorList[SAMPLING_SIZE];
    int slope = 0;
    int speed = 0;

    double error = 0;
    int lastError = 0;
    double reading_r = 0;
    double reading_l = 0;

    int numloops = 0;


    while(slope / SAMPLING_SIZE < STOPPING_ERROR && strength < PICKUP_STRENGTH && numloops > SAMPLING_SIZE){
        
        reading_r = analogRead(IR_RIGHT);
        reading_l = analogRead(IR_LEFT);

        error = reading_r - reading_l;

        strength = reading_r + reading_l;

        p = P_GAIN * error;

        //i = I_GAIN  * error + i;
        
        errorList[0] = (int)error-lastError;
        
        slope = 0;
        for (int i = SAMPLING_SIZE - 1; i >= 1; i--){
            errorList[i] = errorList[i-1];
            slope += errorList[i];
        }
  
        d = D_GAIN * slope / SAMPLING_SIZE; 
        lastError = error;
        
        speed = (int)(p+d)*GAIN;
        //speed = (int)(p+i+d)*GAIN;

        if(IR_DEBUG){
            display.clearDisplay();
            display.setCursor(0,0);
            display.print("right:");
            display.println(reading_r);
            display.print("left:");
            display.println(reading_l);
            display.print("error:");
            display.println(error);
            display.print("speed:");
            display.println(speed);
            display.display();
        }

        turn(speed);
    }

    turn(STOP);



   if(IR_DEBUG){

        display.println("You have reached your destination. Thank you for choosing robot express.");
        display.display();
        delay(1000);
    }

    return true;

}

 bool goToBeacon(int speed, int angular_speed, Adafruit_SSD1306 display){
    
    long starting_time = -LOCKON_INTERVAL - 1; //guarantee that the conditions are met to pont at the beacon

    while(analogRead(IR_LEFT) + analogRead(IR_RIGHT) < STOPPING_STRENGTH){
        
        if(millis() - starting_time > LOCKON_INTERVAL){
            
            if (!pointAtBeacon(angular_speed, display)){
                return false;
            }
            driveStraight(speed);
            
            starting_time = millis();
        }
    }

    driveStraight(STOP);
    return true;
}