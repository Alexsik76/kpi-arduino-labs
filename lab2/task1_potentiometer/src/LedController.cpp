/*
 * File: LedController.cpp
 * Description: Implementation of LED logic with non-blocking timer
 */

#include "LedController.h"

LedController::LedController(int pin, long intervalMs) {
    _pin = pin;
    _interval = intervalMs;
    _ledState = LOW;
    _previousMillis = 0;
    
    pinMode(_pin, OUTPUT);
}

void LedController::turnOn() {
    digitalWrite(_pin, HIGH);
    // Reset state to ensure smooth transition back to blinking if needed
    _ledState = HIGH; 
}

void LedController::turnOff() {
    digitalWrite(_pin, LOW);
    _ledState = LOW;
}

void LedController::blink() {
    unsigned long currentMillis = millis();

    if (currentMillis - _previousMillis >= _interval) {
        _previousMillis = currentMillis;

        // Toggle state
        if (_ledState == LOW) {
            _ledState = HIGH;
        } else {
            _ledState = LOW;
        }
        digitalWrite(_pin, _ledState);
    }
}