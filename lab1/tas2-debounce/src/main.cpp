#include <Arduino.h>

// Variant 14 Constants
const int LED_PIN = 1;        // Calculated: 14 % 13 = 1
const int BUTTON_PIN = 2;     // Button input pin
const int DEBOUNCE_DELAY = 9; // Calculated: 14 % 5 = 4 -> 9 ms

// Global variables for state storage
boolean lastButtonState = LOW; 
boolean ledState = LOW;

// Function prototype
boolean debounce(boolean last);

void setup() {
  // Pin 1 is TX, so Serial.begin() is omitted to avoid conflict with LED
  pinMode(LED_PIN, OUTPUT);
//   digitalWrite(LED_PIN, LOW);
  pinMode(BUTTON_PIN, INPUT);
}

// Debounce function based on Listing 2.5
boolean debounce(boolean last) {
  boolean current = digitalRead(BUTTON_PIN);
  
  if (last != current) {
    delay(DEBOUNCE_DELAY);
    current = digitalRead(BUTTON_PIN);
  }
  
  return current;
}

void loop() {
  boolean currentButtonState = debounce(lastButtonState);

  // Toggle LED on rising edge (transition from LOW to HIGH)
  if (lastButtonState == LOW && currentButtonState == HIGH) {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
  }

  lastButtonState = currentButtonState;
}