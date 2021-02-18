/* 
 * File:   lcd_45.h
 * Author: futurecomp
 *
 * Created on 06 ?????, 2019, 03:15 ?
 */

#ifndef LCD_45_H
#define LCD_45_H

#include "sys.h"
#include <pic18f4550.h>

#define DATA LATD
#define DIR TRISD
#define EN LATD5
#define RS LATD4

void send_cmd(unsigned char cmd);
void _init_lcd(void);
void send_chr(unsigned char chr);
void send_string(unsigned char row,unsigned char col,char *string);
void send_char_pos(unsigned char row,unsigned char col,unsigned char string);

#endif