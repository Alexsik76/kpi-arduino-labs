#ifndef CONFIG_H
#define CONFIG_H

#define STUDENT_VARIANT 14
// Hardware settings
#define LCD_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2
#define SCROLL_DELAY_MS 250 // Speed of scrolling

// Content
// Note: We cannot put Cyrillic directly here comfortably because 
// standard strings don't support custom char mapping automatically.
// We will handle the mapping in the Logic class.

#endif