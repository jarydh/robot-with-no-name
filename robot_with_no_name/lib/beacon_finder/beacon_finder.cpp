// Used for controlling motors
// Authors: Jaryd

#include <beacon_finder.h>
#include <motors.h>
#include <pinout.h>

#define IR_DEBUG TRUE

#define STOP 0

#define STOPPING_STRENGTH 1500 //The sum of readings required to stop
#define PICKUP_STRENGTH 100 //The minimum strength at which a signal is considered to be coming from the beacon
#define TIMEOUT 3000 //Milliseconds before giving up on finding the beacon

#define LOCKON_INTERVAL 2000 //milliseconds between  locking on to the beacon

#define GAIN 1
#define P_GAIN 500
#define D_GAIN 100
#define D_SAMPLING_SIZE 5 //the number of samples used to determine the slope 

bool pointAtBeacon(int angular_speed){
    long starting_time = millis();
    
    if (analogRead(IR_RIGHT) > analogRead(IR_LEFT)) turn(angular_speed);
    else turn(-angular_speed); 

    int strength = 0;
    //rotate until  a signal is picked up, or until timing out
    while(strength < PICKUP_STRENGTH){
        strength = analogRead(IR_LEFT) + analogRead(IR_RIGHT);
        if (millis() - starting_time > TIMEOUT)
            return false;
    }

    //begin PID control
    int p = 0;
    int d = 0;
    int errorList[D_SAMPLING_SIZE];
    int slope = 0;
    int speed = 0;

    double actual = 0;
    double error = 0;
    int lastError = 0;


    while(strength < STOPPING_STRENGTH){
        
        error = analogRead(IR_RIGHT - IR_LEFT);

        strength = analogRead(IR_LEFT) + analogRead(IR_RIGHT);

        p = P_GAIN * GAIN * error;

        errorList[0] = (int)error-lastError;
        
        slope = 0;
        for (int i = D_SAMPLING_SIZE - 1; i >= 1; i--){
            errorList[i] = errorList[i-1];
            slope += errorList[i];
        }
  
        d = D_GAIN * GAIN * slope / D_SAMPLING_SIZE; 
        lastError = error;
        speed = (int)(p+d)/100;
    }

    turn(STOP);

}

 bool goToBeacon(int speed, int angular_speed){

     long starting_time = -LOCKON_INTERVAL - 1; //guarantee that the conditions are met to pont at the beacon

    while(analogRead(IR_LEFT) + analogRead(IR_RIGHT) < STOPPING_STRENGTH){
        
        if(millis() - starting_time > LOCKON_INTERVAL){
            
            if (!pointAtBeacon(angular_speed)){
                return false;
            }
            driveStraight(speed);
            
            starting_time = millis();
        }
    }

    return true;
}