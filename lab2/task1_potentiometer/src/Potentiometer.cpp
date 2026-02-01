/*
 * File: Potentiometer.cpp
 * Description: Implementation of Potentiometer logic
 */

#include "Potentiometer.h"

Potentiometer::Potentiometer(int pin) {
    _pin = pin;
    // Analog pins do not strictly require pinMode, but it's good practice generally
}

int Potentiometer::getValue() {
    return analogRead(_pin);
}