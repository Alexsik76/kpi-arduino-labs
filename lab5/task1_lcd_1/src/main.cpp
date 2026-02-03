/*
 * Lab Work #5 - Task 1
 * Student: Sikorskyi Oleksandr
 * Description: Scrolling text with Mixed Latin/Cyrillic (Custom Chars)
 */

#include "LcdController.h"

LcdController lcdController;

void setup() {
    lcdController.init();
}

void loop() {
    lcdController.update();
}