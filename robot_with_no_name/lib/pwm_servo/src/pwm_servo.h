// Code for driving servo
// Authors: Jaryd

#ifndef PWM_SERVO_H
#define PWM_SERVO_H

#include <Arduino.h>

class pwmServo {
    public:
        // Constructor
        pwmServo(PinName servo_pin)
            : pin(servo_pin) {} 
        void write(int angle);     
    private:
        PinName pin;
};

#endif