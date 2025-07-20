//PIC MASTER <- ATMEGA
#include<xc.h>
#define _XTAL_FREQ 20000000
void I2C_INIT();
void _I2C_START();
void _I2C_STOP();
void I2C_SEND_DATA(char a);
char I2C_READ_DATA(char a);
void TRANSMIT_CHAR(char b);
char mychar;
void main()
{
	int i;
    TRISD=0x00;
    TRISC=0x18;
    TXSTA=0x24;
    RCSTA=0x90;
    SPBRG=129;
    I2C_INIT();
     while(1) {
    _I2C_START();//start slavead+R/w  
    I2C_SEND_DATA(0xd1);//1101 00 d0 and 1
    char m=I2C_READ_DATA(0);
    TRANSMIT_CHAR(m);
     m=I2C_READ_DATA(0);
    TRANSMIT_CHAR(m);
    m=I2C_READ_DATA(1);
    TRANSMIT_CHAR(m);    
    _I2C_STOP();

     }
    
   	
    
}


void I2C_INIT()
{
SSPSTAT=0x80;//1000
SSPCON1=0x28;//
SSPCON2=0x00;
SSPADD=49;
} 
void _I2C_START()
{
SEN=1;
while(SEN==1);//
}

void _I2C_STOP()
{
PEN=1;
while(PEN==1);// 
}
void I2C_SEND_DATA(char a)
{
SSPBUF=a;
SSPIF=0;
while(SSPIF==0);
}
char I2C_READ_DATA(char a)
{
RCEN=1;//receive
while(RCEN);//
while(!BF);
mychar = SSPBUF;
while(BF);
ACKDT=a;//1- NACK before stopping 0->ack
SSPIF = 0;	
ACKEN=1;
while(ACKEN);
SSPIF = 0;	
return mychar;
}
void TRANSMIT_CHAR(char b)
 {
    while(TXIF==0);
    TXREG=b; 
    TXIF=0;
 }
