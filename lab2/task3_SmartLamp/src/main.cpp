/*
 * Lab 2, Task 3: Smart Photo Lamp
 * Variant: 14
 */

#include <Arduino.h>
#include "SmartLamp.h"

// --- Configuration ---
const int VARIANT = 14;

// --- Pins ---
const int PIN_LDR = A0;
const int PIN_LED1 = 9;  
const int PIN_LED2 = 10; 
const int PIN_LED3 = 11; 
const int PIN_BTN = 2;

// --- Objects ---
SmartLamp lamp(PIN_LDR, PIN_LED1, PIN_LED2, PIN_LED3, VARIANT);

// --- Forward Declarations ---
void handleButton();
void handleSerialCommands();

void setup() {
    Serial.begin(9600);
    lamp.setup();
    pinMode(PIN_BTN, INPUT_PULLUP);

    Serial.println(F(">>> Task 3: Smart Lamp Started <<<"));
    Serial.print(F("Variant: ")); Serial.println(VARIANT);
    
    // Debug info
    Serial.print(F("Low Threshold: "));  Serial.println(lamp.getLowThreshold());
    Serial.print(F("High Threshold: ")); Serial.println(lamp.getHighThreshold());

    Serial.println(F("Controls: [Button] Power, [1] Step Mode, [2] Smooth Mode"));
}

void loop() {
    // 1. Input Handling
    handleButton();
    handleSerialCommands();

    // 2. Logic Update
    lamp.update();
    
    delay(10); // Small stability delay
}

// --- Helper Functions ---

void handleButton() {
    // Static variables preserve their value between function calls
    // They are initialized only once
    static bool lastBtnState = HIGH;
    static bool stableState = HIGH;
    static unsigned long lastDebounceTime = 0;
    const unsigned long DEBOUNCE_DELAY = 50;

    bool reading = digitalRead(PIN_BTN);

    // If the switch changed, due to noise or pressing:
    if (reading != lastBtnState) {
        lastDebounceTime = millis();
    }
    
    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
        // Whatever the reading is at, it's been there for longer than the debounce
        // delay, so take it as the actual current state:

        if (reading != stableState) {
            stableState = reading;

            // Only toggle power if the new button state is LOW (Pressed)
            if (stableState == LOW) {
                lamp.togglePower();
                Serial.print(F("Power: "));
                Serial.println(lamp.isOn() ? F("ON") : F("OFF"));
            }
        }
    }
    
    lastBtnState = reading;
}

void handleSerialCommands() {
    if (Serial.available() > 0) {
        int cmd = Serial.parseInt();
        
        // Clear the buffer to avoid processing newline characters
        while(Serial.available()) Serial.read(); 

        if (cmd == 1) {
            lamp.setMode(MODE_STEP);
            Serial.println(F("Mode: STEP"));
        } else if (cmd == 2) {
            lamp.setMode(MODE_SMOOTH);
            Serial.println(F("Mode: SMOOTH"));
        }
    }
}