#include<xc.h>
#define _XTAL_FREQ 20000000
void my_char(char data);
unsigned char data;
void main(){
  TRISC = 0X98;
  TXSTA = 0x24;
  RCSTA = 0x90;
  SPBRG = 129;
  TRISB = 0X00;
  PORTB = 0X00;
SSPSTAT =0x80; 
SSPCON1 =0x36; 
SSPCON2 =0x01;
SSPADD = 0xd0;


while(1){
    if(SSPSTAT & 0X08){
        SSPOV = 0;
        data =SSPBUF;
    }
    if(SSPIF){
        CKP = 0;
        if(!(SSPSTAT & 0x04)){
          data = SSPBUF;
          while(BF);
          
          SSPIF =0;
        }
        SSPOV = 0;
        if(data != SSPADD){
        my_char(data);
        }
        CKP = 1;
        
    }
   }
}
void my_char(char d){
    TXREG = d;
    while(!TXIF);
    TXIF = 0;
}

