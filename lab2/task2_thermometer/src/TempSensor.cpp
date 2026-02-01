/*
 * File: TempSensor.cpp
 * Description: Implementation of NTC logic
 */

#include "TempSensor.h"

TempSensor::TempSensor(uint8_t pin) {
    _pin = pin;
}

float TempSensor::getCelsius() {
    int analogValue = analogRead(_pin);

    // Safety check to avoid division by zero or log(0) errors
    // if sensor is disconnected or shorted
    if (analogValue == 0 || analogValue >= 1023) {
        return -273.15; // Return absolute zero as error code
    }

    // Formula provided in documentation for NTC 3950
    // 1 / (log(1 / (1023. / analogValue - 1)) / BETA + 1.0 / 298.15) - 273.15
    
    float celsius = 1.0 / (log(1.0 / (1023.0 / analogValue - 1.0)) / BETA + 1.0 / 298.15) - 273.15;
    
    return celsius;
}

float TempSensor::getFahrenheit() {
    float c = getCelsius();
    return (c * 9.0 / 5.0) + 32.0;
}