#ifndef FILE_LCD_H
#define FILE_LCD_H
#include <main.h>
bit lcd_busy(void);
void lcd_wcmd(uchar cmd);
void lcd_wdat(uchar dat);
void lcd_init(void);
void lcd_pos(uchar pos);
#endif 