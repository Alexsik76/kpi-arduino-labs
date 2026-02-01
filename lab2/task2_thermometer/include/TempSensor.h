/*
 * File: TempSensor.h
 * Description: Class for NTC Thermistor using Beta coefficient formula
 */

#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

#include <Arduino.h>

class TempSensor {
private:
    uint8_t _pin;
    const float BETA = 3950.0; // Beta Coefficient matching the simulation part

public:
    // Constructor
    TempSensor(uint8_t pin);

    // Calculates temperature in Celsius using the Beta equation
    float getCelsius();

    // Converts Celsius to Fahrenheit
    float getFahrenheit();
};

#endif