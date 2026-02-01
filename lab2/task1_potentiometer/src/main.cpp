

// Variant 14 Constants
/*
 * Main Sketch
 * Project: Potentiometer Controlled LED
 * Architecture: Modular & Parametric
 */
#include <Arduino.h>

#include "Potentiometer.h"
#include "LedController.h"

// --- Configuration ---
const int VARIANT = 14;  

const int POT_PIN = A0;
const int LED_PIN = 3;

// --- Calculated Constants ---
const int MIN_RANGE = (VARIANT % 30) * 20;
const int MAX_RANGE = (VARIANT % 30) * 40;
const int COMMAND_CODE = VARIANT; 

// --- Global Objects ---
Potentiometer pot(POT_PIN);
LedController led(LED_PIN);

// --- State Variables ---
bool isBlinkingMode = false;

// --- Forward Declarations ---
void handleUserCommands();
void updateLedState(int sensorValue);
void logSystemStatus(int sensorValue);

void setup() {
    Serial.begin(9600);
    
    Serial.print(F("System Initialized for Variant: "));
    Serial.println(VARIANT);
    Serial.print(F("Active Range: "));
    Serial.print(MIN_RANGE);
    Serial.print(F(" - "));
    Serial.println(MAX_RANGE);
    Serial.println(F("Send your variant number to toggle mode."));
}

void loop() {
    // 1. INPUT
    int val = pot.getValue();

    // 2. LOGIC
    handleUserCommands();

    // 3. OUTPUT
    updateLedState(val);

    // 4. LOGGING (Опціонально)
    logSystemStatus(val);

    delay(50); 
}

// --- Helper Functions ---

void handleUserCommands() {
    if (Serial.available() > 0) {
        int incoming = Serial.parseInt();
        
        while (Serial.available() > 0) Serial.read(); // Flush buffer

        if (incoming == COMMAND_CODE) {
            isBlinkingMode = !isBlinkingMode;
            
            if (isBlinkingMode) {
                Serial.println(F(">>> MODE: Blinking Enabled <<<"));
            } else {
                Serial.println(F(">>> MODE: Steady Light <<<"));
            }
        }
    }
}

void updateLedState(int sensorValue) {
    bool isInRange = (sensorValue >= MIN_RANGE && sensorValue <= MAX_RANGE);

    if (isInRange) {
        if (isBlinkingMode) {
            led.blink();
        } else {
            led.turnOn();
        }
    } else {
        led.turnOff();
    }
}

void logSystemStatus(int sensorValue) {
    Serial.print("Pot Value: ");
    Serial.print(sensorValue);
    if (sensorValue >= MIN_RANGE && sensorValue <= MAX_RANGE) {
        Serial.println(" [ACTIVE ZONE]");
    } else {
        Serial.println("");
    }
}