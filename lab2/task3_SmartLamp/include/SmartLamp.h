#ifndef SMARTLAMP_H
#define SMARTLAMP_H

#include <Arduino.h>

enum LampMode {
    MODE_STEP = 1,   // Step mode (3 levels)
    MODE_SMOOTH = 2  // Smooth mode (PWM)
};

class SmartLamp {
private:
    uint8_t _pinLdr;
    uint8_t _pinLed1, _pinLed2, _pinLed3;
    
    // Dynamic thresholds based on variant
    int _valLow;
    int _valMiddle;
    int _valHigh;

    LampMode _currentMode;
    bool _isOn;

    void runStepMode(int luxValue);
    void runSmoothMode(int luxValue);

public:
    // Constructor now accepts 'variant' to calculate thresholds dynamically
    SmartLamp(uint8_t pLdr, uint8_t l1, uint8_t l2, uint8_t l3, int variant);
    
    void setup();
    void update(); 
    void togglePower();
    void setMode(LampMode mode);
    bool isOn();
    
    // Getters for debugging
    int getLowThreshold();
    int getHighThreshold();
};

#endif