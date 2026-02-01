#include "SmartLamp.h"

SmartLamp::SmartLamp(uint8_t pLdr, uint8_t l1, uint8_t l2, uint8_t l3, int variant) {
    _pinLdr = pLdr;
    _pinLed1 = l1;
    _pinLed2 = l2;
    _pinLed3 = l3;
    
    _currentMode = MODE_STEP;
    _isOn = true; 

    // Calculate thresholds based on Variant (n)
    // Formula: low = (350 - n%30 * 2)
    _valLow = 350 - (variant % 30) * 2;

    // Formula: high = (700 + n%30 * 4)
    _valHigh = 700 + (variant % 30) * 4;

    // Middle point (between Low and High)
    _valMiddle = (_valLow + _valHigh) / 2;
}

void SmartLamp::setup() {
    pinMode(_pinLed1, OUTPUT);
    pinMode(_pinLed2, OUTPUT);
    pinMode(_pinLed3, OUTPUT);
}

void SmartLamp::togglePower() {
    _isOn = !_isOn;
    if (!_isOn) {
        digitalWrite(_pinLed1, LOW);
        digitalWrite(_pinLed2, LOW);
        digitalWrite(_pinLed3, LOW);
    }
}

void SmartLamp::setMode(LampMode mode) {
    _currentMode = mode;
}

bool SmartLamp::isOn() { return _isOn; }

int SmartLamp::getLowThreshold() { return _valLow; }
int SmartLamp::getHighThreshold() { return _valHigh; }

void SmartLamp::update() {
    if (!_isOn) return;

    int val = analogRead(_pinLdr);

    if (_currentMode == MODE_STEP) {
        runStepMode(val);
    } else {
        runSmoothMode(val);
    }
}

void SmartLamp::runStepMode(int val) {
    // Logic:
    // < Low: 3 LEDs
    // Low..Mid: 2 LEDs
    // Mid..High: 1 LED
    // > High: 0 LEDs
    
    int ledCount = 0;
    if (val < _valLow) ledCount = 3;
    else if (val < _valMiddle) ledCount = 2;
    else if (val < _valHigh) ledCount = 1;
    else ledCount = 0;

    digitalWrite(_pinLed1, ledCount >= 1 ? HIGH : LOW);
    digitalWrite(_pinLed2, ledCount >= 2 ? HIGH : LOW);
    digitalWrite(_pinLed3, ledCount >= 3 ? HIGH : LOW);
}

void SmartLamp::runSmoothMode(int val) {
    // Constrain input to active range
    int constrainedVal = constrain(val, _valLow, _valHigh);
    
    // Inverse mapping: Low val -> Max Brightness (255), High val -> Off (0)
    int pwm = map(constrainedVal, _valLow, _valHigh, 255, 0);

    analogWrite(_pinLed1, pwm);
    analogWrite(_pinLed2, pwm);
    analogWrite(_pinLed3, pwm);
}