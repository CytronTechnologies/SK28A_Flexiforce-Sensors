/* 
 * File:   lcd.h
 * Author: Hatake_Chin
 *
 * Created on July 26, 2012, 10:59 PM
 */

#ifndef LCD_H
#define	LCD_H

extern void LCD_command (unsigned char var);

extern void LCD_initialize();

extern void LCD_senddata(unsigned char var);

extern void LCD_putstr(char* csz_string);

extern void LCD_putchar(char c_data);

extern void LCD_clear();

extern void LCD_goto(unsigned char row,unsigned char column);

extern void LCD_4bitsend(unsigned char data);

#endif	/* LCD_H */

