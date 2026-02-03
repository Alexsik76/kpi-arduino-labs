#ifndef LCD_CONTROLLER_H
#define LCD_CONTROLLER_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h> 
#include "Config.h"
#include "Glyphs.h"

class LcdController {
private:
    LiquidCrystal_I2C lcd;
    unsigned long lastUpdate;
    unsigned int scrollPosition;
    
    bool isReverse; 

    String row0Text;
    String row1Text;
    
    const char CHAR_k = 1;
    const char CHAR_sft = 2;
    const char CHAR_y = 3;
    const char CHAR_yi = 4;
    const char CHAR_l = 5;
    const char CHAR_n = 6;
    const char CHAR_d = 7;

public:
    LcdController();
    void init();
    void update(); 
    
private:
    void uploadCustomChars();
    void setContent();
    void determineDirection(); 
};

#endif