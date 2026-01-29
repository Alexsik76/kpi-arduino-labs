#include <Arduino.h>

// Variant 14
const int n = 14;

// PWM Pin (Pins 3, 5, 6, 9, 10, 11 support PWM on Uno)
const int LED_PIN = 3; 

// Calculate brightness limits based on formula:
// min = n % 30
// max = 255 - n % 30
const int MIN_BRIGHTNESS = n % 30;         // Result: 14
const int MAX_BRIGHTNESS = 255 - (n % 30); // Result: 241

void setup() {
  pinMode(LED_PIN, OUTPUT);
  
  Serial.begin(9600);
  Serial.print("Variant: "); Serial.println(n);
  Serial.print("Min Brightness: "); Serial.println(MIN_BRIGHTNESS);
  Serial.print("Max Brightness: "); Serial.println(MAX_BRIGHTNESS);
}

void loop() {
  // Fade in from min to max
  for (int i = MIN_BRIGHTNESS; i <= MAX_BRIGHTNESS; i++) {
    analogWrite(LED_PIN, i);
    delay(1); // Small delay to make the effect visible
  }

  // Fade out from max to min
  for (int i = MAX_BRIGHTNESS; i >= MIN_BRIGHTNESS; i--) {
    analogWrite(LED_PIN, i);
    delay(1);
  }
}