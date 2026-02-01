/*
 * File: Potentiometer.h
 * Description: Interface for analog potentiometer sensor
 */

#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <Arduino.h>

class Potentiometer {
private:
    int _pin;

public:
    // Constructor
    Potentiometer(int pin);

    // Get current analog value (0-1023)
    int getValue();
};

#endif