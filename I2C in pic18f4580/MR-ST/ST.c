/*
 * File:   ST.c
 * Author: LENOVO
 *
 * Created on 19 January, 2025, 8:48 PM
 */


#include <xc.h>
#define _XTAL_FREQ 20000000
void data(const char d);
void string(const char *s);
int i;
void main(void) {
    SSPADD = 0Xd0;
    SSPSTAT = 0X80;
    SSPCON1 = 0X36;
    SSPCON2 = 0x01;
    TRISC = 0xff;
    while(1){
         if(SSPSTAT & 0X08){
        SSPOV = 0;
        data =SSPBUF;
    }
      
        if(CKP==0){
            if(SSPSTAT & 0X04){
                char dummy = SSPBUF;
                SSPBUF = 40 + i++;
                while(!BF);
                
                
                CKP =1;
                SSPIF = 0;
                
                
                
               // __delay_ms(5);
            }
        }
    }

    return;
}

