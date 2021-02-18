/* 
 * File:   keypad.h
 * Author: M.Magdy
 *
 * Created on February 27, 2020, 6:34 PM
 */

#include "sys.h"
#include <pic18f4550.h>

#ifndef KEYPAD_H
#define	KEYPAD_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    #define write_port LATB
    #define read_port PORTB
    #define dir_port TRISB

#define keypadfind_enable 1
#if(keypadfind_enable == 1)
    unsigned char keypadfind(void);
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* KEYPAD_H */

