#include<pic18.h>
#define _XTAL_FREQ 20000000
void I2C_INIT();
void _I2C_STOP();
void I2C_SEND_DATA(char a);
char I2C_READ_DATA(char a);
void _I2C_START();
void string(const char *s);
void main()
{
TRISB=TRISD=0x00;
TRISC=0x18;

for(long i=0;i<100000;i++);//delay
I2C_INIT();
while(1){
_I2C_START();//start slave ad+R/w  
for(long i=0;i<100000;i++);//delay
I2C_SEND_DATA(0xd0);//1101 000 0
string("hello world\n\r");
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
void I2C_SEND_DATA(const char a)
{
SSPBUF=a;
SSPIF=0;

while(SSPIF==0);
}
void string(const char *s){
    while(*s){
        
     I2C_SEND_DATA(*s++);   
    }
}

