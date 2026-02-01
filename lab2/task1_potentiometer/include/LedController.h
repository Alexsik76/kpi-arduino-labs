/*
 * File: LedController.h
 * Description: Interface for LED control (blink/steady)
 */

#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include <Arduino.h>

class LedController {
private:
    int _pin;
    unsigned long _previousMillis;
    int _ledState;
    long _interval;

public:
    // Constructor
    LedController(int pin, long intervalMs = 500);

    void turnOn();
    void turnOff();
    
    // Non-blocking blink method
    void blink();
};

#endif