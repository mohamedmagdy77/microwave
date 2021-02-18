/* 
 * File:   keypad.c
 * Author: M.Magdy
 *
 * Created on February 27, 2020, 6:36 PM
 */

#include "keypad.h"
#include "delay.h"

#if(keypadfind_enable == 1)
unsigned char col_pos,row_pos;
unsigned char keypad[4][4] = {{'7','8','9','/'}
                                ,{'4','5','6','*'}
                                ,{'1','2','3','-'}
                                ,{' ','0','=','+'}};


unsigned char keypadfind(void){
    dir_port = 0xf0;
    write_port = 0xf0;
    col_pos = read_port;
    while(col_pos == 0xf0){
        col_pos = read_port;
    }
   
    write_port = 0xfe;
    row_pos = read_port;
    if(row_pos != 0xfe){
        row_pos = 0;
        while(read_port != 0xfe){}
        goto label;
    }
    write_port = 0xfd;
    row_pos = read_port;
    if(row_pos != 0xfd){
        row_pos = 1;
        while(read_port != 0xfd){} 
        goto label;
    }
    write_port = 0xfb;
    row_pos = read_port;
    if(row_pos != 0xfb){
        row_pos = 2;
        while(read_port != 0xfb){} 
        goto label;
    }
    write_port = 0xf7;
    row_pos = read_port;
    if(row_pos != 0xf7){
        row_pos = 3;
        while(read_port != 0xf7){}  
        goto label;
    }
    label:
    switch(col_pos){
        case 0xe0:
            col_pos = 0;
            break;
        case 0xd0:
            col_pos = 1;
            break;
        case 0xb0:
            col_pos = 2;
            break;
        case 0x70:
            col_pos = 3;
            break;
    }
    MSdelay(100);
    return keypad[row_pos][col_pos];
}
#endif
