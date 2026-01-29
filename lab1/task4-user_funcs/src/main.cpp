#include <Arduino.h>

// --- Hardware Constants ---
const int BUTTON_PIN = 2;
const int LED_PIN = 3;

// --- PWM Configuration ---
const int MIN_BRIGHTNESS = 14;
const int MAX_BRIGHTNESS = 241;
const int FADE_STEP_DELAY = 10; // Time in ms between brightness steps

// --- State Definitions ---
enum SystemState {
    STATE_OFF,              // 0: LED is Off
    STATE_FADE_UP,          // 1: Fading form Min to Max
    STATE_FADE_DOWN,        // 2: Fading from Max to Min
    STATE_MAX_STEADY        // 3: LED is On at Max brightness
};

// --- Global Variables ---
SystemState currentState = STATE_OFF;
int currentBrightness = 0;
unsigned long lastFadeTime = 0;

// --- Function Prototypes ---
bool isButtonPressed();
void nextState();
void runStateLogic();

void setup() {
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT); // External 10k pull-down resistor assumed
    
    analogWrite(LED_PIN, 0);
    
    Serial.begin(9600);
    Serial.println("System Initialized. State: OFF");
}

void loop() {
    // 1. Input Processing
    if (isButtonPressed()) {
        nextState(); // Handle state transition and initialization
    }

    // 2. Logic Execution
    runStateLogic(); // Handle continuous behavior (fading)
}

// --- Transition Logic ---
// Responsible for switching states and initializing variables for the new state
void nextState() {
    // Cycle through states: 0 -> 1 -> 2 -> 3 -> 0
    switch (currentState) {
        case STATE_OFF:
            currentState = STATE_FADE_UP;
            currentBrightness = MIN_BRIGHTNESS; // Reset brightness for fade up
            break;
            
        case STATE_FADE_UP:
            currentState = STATE_FADE_DOWN;
            currentBrightness = MAX_BRIGHTNESS; // Reset brightness for fade down
            break;
            
        case STATE_FADE_DOWN:
            currentState = STATE_MAX_STEADY;
            break;
            
        case STATE_MAX_STEADY:
            currentState = STATE_OFF;
            break;
    }

    Serial.print("State Changed To: ");
    Serial.println(currentState);
}

// --- Main State Machine ---
// Responsible for the ongoing behavior of the active state
void runStateLogic() {
    unsigned long currentTime = millis();

    switch (currentState) {
        case STATE_OFF:
            analogWrite(LED_PIN, 0);
            break;

        case STATE_FADE_UP:
            if (currentTime - lastFadeTime >= FADE_STEP_DELAY) {
                lastFadeTime = currentTime;
                if (currentBrightness < MAX_BRIGHTNESS) {
                    currentBrightness++;
                    analogWrite(LED_PIN, currentBrightness);
                }
            }
            break;

        case STATE_FADE_DOWN:
            if (currentTime - lastFadeTime >= FADE_STEP_DELAY) {
                lastFadeTime = currentTime;
                if (currentBrightness > MIN_BRIGHTNESS) {
                    currentBrightness--;
                    analogWrite(LED_PIN, currentBrightness);
                }
            }
            break;

        case STATE_MAX_STEADY:
            analogWrite(LED_PIN, MAX_BRIGHTNESS);
            break;
    }
}

// --- Input Handler ---
// Uses "Stability Check" method: robust against both press and release noise.
// Latency reduced to 20ms for better responsiveness.
bool isButtonPressed() {
    static bool lastReading = LOW;
    static unsigned long lastDebounceTime = 0;
    static bool confirmedState = LOW; // The actual stable state of the button

    // 20ms is usually enough for tactile switches and feels instant to humans
    const unsigned long DEBOUNCE_DELAY = 20; 

    bool reading = digitalRead(BUTTON_PIN);
    bool pressed = false;

    // If the switch changed, due to noise or pressing:
    if (reading != lastReading) {
        lastDebounceTime = millis(); // Reset the timer
    }

    // If the reading has been stable for DEBOUNCE_DELAY:
    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
        
        // If the stable reading is different from our last confirmed state
        if (reading != confirmedState) {
            confirmedState = reading;

            // Only trigger on Rising Edge (LOW -> HIGH)
            if (confirmedState == HIGH) {
                pressed = true;
            }
        }
    }

    lastReading = reading;
    return pressed;
}