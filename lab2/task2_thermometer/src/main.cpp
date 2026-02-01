/*
 * Lab 2, Task 2: NTC Thermistor Thermometer
 * Variant: 14 (Update interval 700 ms)
 */

#include <Arduino.h>
#include "TempSensor.h"

// --- Configuration ---
const int VARIANT = 14;
const int SENSOR_PIN = A0; 

// Interval calculation: (14 % 30) * 50 = 700 ms
const unsigned long UPDATE_INTERVAL = (VARIANT % 30) * 50;

// --- Global Objects ---
TempSensor sensor(SENSOR_PIN);

// --- State Variables ---
unsigned long previousMillis = 0;

void setup() {
    Serial.begin(9600);
    
    Serial.println(F(">>> Task 2: NTC Thermometer Started <<<"));
    // A little delay to stabilize ADC
    delay(100);
}

void loop() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= UPDATE_INTERVAL) {
        previousMillis = currentMillis;

        float c = sensor.getCelsius();
        float f = sensor.getFahrenheit();

        Serial.print("T: ");
        Serial.print(c, 1); 
        Serial.print(" C | ");
        Serial.print(f, 1);
        Serial.println(" F");
    }
}