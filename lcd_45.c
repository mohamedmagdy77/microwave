/* 
 * File:   lcd_45.c
 * Author: futurecomp
 *
 * Created on 06 ?????, 2019, 03:15 ?
 */

#include "lcd_45.h"
#include "delay.h"

//----------------------------------------------------------------------------
void send_cmd(unsigned char cmd){
    unsigned char copy = cmd;
    DATA = (DATA & 0xF0) | (copy >> 4);
    RS = 0;
    EN = 1;
    NOP();
    EN = 0;
    MSdelay(1);
    
    DATA = (DATA & 0xF0) | (cmd & 0x0F);
    EN = 1;
    NOP();
    EN = 0;
    MSdelay(3);
}
//------------------------------------------------------------------

void _init_lcd(void){
    DIR = 0;
    MSdelay(15);
    send_cmd(0x02);     //display and cursor home
    send_cmd(0x28);     //2_line mode , 5*7 mode
    send_cmd(0x01);     //clear display
    
    send_cmd(0x0c);     //display on & cursor underline and blink off
    send_cmd(0x14);     //
    send_cmd(0x06);
    
}
//-----------------------------------------------------------------------
void send_chr(unsigned char chr){
    unsigned char copy = chr;
    DATA = (DATA & 0xF0) | (copy >> 4);
    RS = 1;
    EN = 1;    
    NOP();
    EN = 0;
    MSdelay(1);

    DATA = (DATA & 0xF0) | (chr & 0x0F);    
    EN = 1;
    NOP();
    EN = 0;
    MSdelay(3);
}
//---------------------------------------------------------------------------
void send_string(unsigned char row,unsigned char col,char *string){
    unsigned char loc;
    if(row==1){
        loc = 0x80 | (col & 0x0F);
        send_cmd(loc);
    }
    else{
        loc = 0xc0 | (col & 0x0F);
        send_cmd(loc);        
    }
    while((*string) != '\0'){
        send_chr(*string);
        string++;
    }
}
//---------------------------------------------------------------------------
void send_char_pos(unsigned char row,unsigned char col,unsigned char string){
    unsigned char loc;
    if(row==1){
        loc = 0x80 | (col & 0x0F);
        send_cmd(loc);
    }
    else{
        loc = 0xc0 | (col & 0x0F);
        send_cmd(loc);        
    }
        send_chr(string);
}
