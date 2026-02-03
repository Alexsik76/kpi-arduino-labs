#include "LcdController.h"

LcdController::LcdController() : lcd(LCD_ADDR, LCD_COLS, LCD_ROWS) {
    lastUpdate = 0;
    scrollPosition = 0;
    isReverse = false;
}

void LcdController::init() {
    lcd.init();
    lcd.backlight();
    
    determineDirection(); 
    uploadCustomChars();
    setContent();
}

void LcdController::determineDirection() {

    if (STUDENT_VARIANT % 2 != 0) {
        isReverse = true; 
    } else {
        isReverse = false;
    }
}

void LcdController::uploadCustomChars() {
    uint8_t buffer[8];
    memcpy_P(buffer, GLYPH_k, 8);   lcd.createChar(CHAR_k, buffer);
    memcpy_P(buffer, GLYPH_sft, 8); lcd.createChar(CHAR_sft, buffer);
    memcpy_P(buffer, GLYPH_y, 8);   lcd.createChar(CHAR_y, buffer);
    memcpy_P(buffer, GLYPH_yi, 8);  lcd.createChar(CHAR_yi, buffer);
    memcpy_P(buffer, GLYPH_l, 8);   lcd.createChar(CHAR_l, buffer);
    memcpy_P(buffer, GLYPH_n, 8);   lcd.createChar(CHAR_n, buffer);
    memcpy_P(buffer, GLYPH_d, 8);   lcd.createChar(CHAR_d, buffer);
}

void LcdController::setContent() {
    String surname = "";
    surname += 'C'; surname += 'i'; surname += CHAR_k; surname += 'o'; surname += 'p';
    surname += 'c'; surname += CHAR_sft; surname += CHAR_k; surname += CHAR_y; surname += CHAR_yi;

    String name = "";
    name += 'O'; name += CHAR_l; name += 'e'; name += CHAR_k; name += 'c';
    name += 'a'; name += CHAR_n; name += CHAR_d; name += 'p';

    String padding = "                "; 
    
    row0Text = padding + surname + padding;
    row1Text = padding + name + padding;
}

void LcdController::update() {
    if (millis() - lastUpdate >= SCROLL_DELAY_MS) {
        lastUpdate = millis();
        
        unsigned int maxLen = max(row0Text.length(), row1Text.length());
        unsigned int maxScroll = maxLen - LCD_COLS; 

        int currentPos;

        if (isReverse) {
            
            currentPos = maxScroll - scrollPosition;
        } else {
            currentPos = scrollPosition;
        }

        lcd.setCursor(0, 0);
        String sub0 = row0Text.substring(currentPos, currentPos + LCD_COLS);
        lcd.print(sub0);
        
        lcd.setCursor(0, 1);
        String sub1 = row1Text.substring(currentPos, currentPos + LCD_COLS);
        lcd.print(sub1);
        
        // Оновлення лічильника
        scrollPosition++;
        if (scrollPosition > maxScroll) {
            scrollPosition = 0;
        }
    }
}