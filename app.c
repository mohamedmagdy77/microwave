/*
 * File:   app.c
 * Author: M.Magdy
 * Microwave project
 * Created on March 4, 2020, 4:43 PM
 */


#include "lcd_45.h"
#include "keypad.h"
#include "delay.h"


#define FAN    LATC0 
#define LIGHT  LATC1
#define START  RC2
#define STOP   RC4
#define DOOR   RC5
#define WEIGHT RC6
#define HEATER LATC7


/*........................parameters of code..........*/
unsigned char time_recieve, time_recieve_arr[6], time_lcd[6]={0,1,3,4,6,7};
unsigned char logic=0, zeros, ended=0;
/*...............declarations.........................*/
void init(void);
void recieve_time(void);
void init_timer0(void);
unsigned char num_zeros(void);


void __interrupt() Timer0_ISR(){
    if((INTCON&(1<<2)) == 4){
        TMR0 = 0xc2f6;
        if(time_recieve_arr[5]<'1'){
            int i;
            for(i=5;i>=0;i--){
                if(time_recieve_arr[i]!='0'){
                    break;
                }
            }
            time_recieve_arr[i]--;
            for(int x=i+1;x<6;x++){
                x%2 ? (time_recieve_arr[x]='9') : (time_recieve_arr[x]='5');
            }
            if(time_recieve_arr[zeros] < '1'){
                time_recieve_arr[zeros]='0';
                    zeros++;
                    }
            logic = 1;
            /*int j;
            for(j=5;j>=zeros;j--){
                if(time_recieve_arr[j]<'1'){
                    j%2 ? (time_recieve_arr[j]='9') : (time_recieve_arr[j]='5');
                    time_recieve_arr[j-1]--;
                    if(time_recieve_arr[zeros] < '1'){
                        time_recieve_arr[j-1]='0';
                        zeros++;
                    }
                    logic=1;
                }
            }*/
        }
        else{
           time_recieve_arr[5]--; 
           logic=1;
        }
        /*this part for when time ends*/
        if(zeros==5 && time_recieve_arr[5]=='0'){
            ended = 1;
        }
        INTCON &= ~(1<<2);      //clear timer0 flag
    }
}

/*.........................main.......................*/
void main(void) {
    label1:
    init();
    init_timer0();
    recieve_time();
    zeros = num_zeros();
    while(START==1 || WEIGHT==1 || DOOR==1){}
    FAN = 1;
    LIGHT = 1;
    HEATER = 1;
    T0CON |= (1<<7);    //enable timer0
    while(STOP){
        if(logic == 1){
            for(int z=0;z<6;z++){
                send_char_pos(2,time_lcd[z],time_recieve_arr[z]);
            }
            logic = 0;
        }
        if(ended == 1){
            T0CON &= ~(1<<7);   //timer0 off
            FAN = 0;
            LIGHT = 0;
            HEATER = 0;
            ended = 0;
            for(int z=0;z<6;z++){
                send_cmd(0x01);
                send_string(1,0,"time ended");
                MSdelay(300);
            }
            goto label1;
        }
    }
}
//........................................................
void init(void){
    OSCCON = 0x72;          /*clock frequency 8 MHz*/
    TRISC = 0x7c;           /*inputs and outputs*/
    LATC = 0x00;            /*all outputs are zeros*/
    INTCON2 &= ~(1<<7);     /*pull_up PORTB*/
    _init_lcd();            
    send_string(1,0,"time setting");

}
//........................................................
void recieve_time(void){
    int i;
    label:
    send_string(2,0,"**:**:**  ");
    for(i=0;i<6;i++){
        time_recieve = keypadfind();
        if(i==0 || i==2 || i==4){
            if(time_recieve>'5'){
                send_string(2,0,"time error");
                MSdelay(1000);
                goto label;
            }
        }
        send_char_pos(2,time_lcd[i],time_recieve);
        time_recieve_arr[i] = time_recieve;
    }
}
//........................................................
void init_timer0(void){
    T0CON = 0x06;       //1:128      
    TMR0 = 0xfff6;
    INTCON = 0xe0;
}
//........................................................
/*to know number of digits entered*/
unsigned char num_zeros(void){
    for(int i=0;i<6;i++){
        if(time_recieve_arr[i]!='0'){
            return i;
        }
    }
    return 0;
}


