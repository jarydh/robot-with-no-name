// Code for using sonar
// Authors: Jaryd

#ifndef SONAR_H
#define SONAR_H

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Ultrasonic.h>

#define NUM_SONAR_READINGS 3

class sonarWrapper{
    public:
        // Constructor
        sonarWrapper(Ultrasonic& sonar, Adafruit_SSD1306& display)
            : sonar_ptr(sonar), display_ptr(display) {}      
        void setSonarRange(int range);
        int readSonar();
        void resetSonar();
    private:
        int sonar_readings[NUM_SONAR_READINGS];
        Ultrasonic& sonar_ptr;
        Adafruit_SSD1306& display_ptr;
};

#endif