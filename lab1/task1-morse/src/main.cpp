#include <Arduino.h>
#include <ctype.h>

const int LED_PIN = LED_BUILTIN;

// Standard Morse Code Timing
const int DOT_DURATION = 200;            // Base time unit (T)
const int DASH_DURATION = DOT_DURATION * 3;
const int SYMBOL_GAP = DOT_DURATION;     // Gap between signals within a char (1T)
const int LETTER_GAP = DOT_DURATION * 3; // Gap between characters (3T)
const int WORD_GAP = DOT_DURATION * 7;   // Gap between words (7T)

// Signal type definition for type safety
enum Signal {
    DOT,
    DASH
};

// Morse Code Lookup Table (A-Z)
const char* MORSE_LETTERS[] = {
    ".-",   "-...", "-.-.", "-..",  ".",    "..-.", "--.",  "....", "..",   ".---", // A-J
    "-.-",  ".-..", "--",   "-.",   "---",  ".--.", "--.-", ".-.",  "...",  "-",    // K-T
    "..-",  "...-", ".--",  "-..-", "-.--", "--.."                                  // U-Z
};

// Function Prototypes (Good practice in C++, helps compiler)
void play_signal(Signal signal);
void play_char(char c);

void setup() {
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(9600);
}

// Executes a single signal (Dot or Dash)
void play_signal(Signal signal) {
    int duration = (signal == DOT) ? DOT_DURATION : DASH_DURATION;

    digitalWrite(LED_PIN, HIGH);
    delay(duration);
    digitalWrite(LED_PIN, LOW);
    
    // Always add standard inter-element gap after a signal
    delay(SYMBOL_GAP);
}

// Parses and plays a full character
void play_char(char c) {
    char upper_c = toupper(c);

    // Handle Letters (A-Z)
    if (upper_c >= 'A' && upper_c <= 'Z') {
        int index = upper_c - 'A';
        const char* sequence = MORSE_LETTERS[index];
        
        Serial.print("Letter: ");
        Serial.print(upper_c);
        Serial.print(" -> ");
        Serial.println(sequence);

        // Parse sequence and play valid signals only
        for (int i = 0; sequence[i] != '\0'; i++) {
            if (sequence[i] == '.' || sequence[i] == '-') {
                Signal signal = (sequence[i] == '.') ? DOT : DASH;
                play_signal(signal);
            }
        }
        
        // Compensate for the SYMBOL_GAP added by the last signal
        delay(LETTER_GAP - SYMBOL_GAP); 
    } 
    // Handle Space (Word Gap)
    else if (upper_c == ' ') {
        // Compensate for the LETTER_GAP added by the previous character
        delay(WORD_GAP - LETTER_GAP);
        Serial.println(" (Space) ");
    }
}

void loop() {
    const char* message = "SIK";
    
    for (int i = 0; message[i] != '\0'; i++) {
        play_char(message[i]);
    }
    
    // Visual separator between loops
    Serial.println("-------------------");
    delay(3000); // Pause before repeating loop
}