#define F_CPU 8000000UL
#include <avr/io.h>
#include <xc.h>
#include <util/delay.h>

#define SCL_CLOCK 100000  // 100kHz standard I2C speed
#define SLA_W 0xD0         // Slave address + Write bit (0x68 << 1 = 0xD0)

void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Write(uint8_t data);

int main(void)
{
    I2C_Init();        // Initialize I2C master
    _delay_ms(100);    // Small delay for stability

    I2C_Start();       // Send start condition
    I2C_Write(SLA_W);  // Send slave address + Write (0xD0)
    for(int i=0;i<11;i++){
    I2C_Write(i+'0');   // Send first byte
    }   // Send second byte

    I2C_Stop();        // Send stop condition

    while (1);         // Done
}
void I2C_Init(void)
{
    // Set bit rate: TWBR = ((F_CPU / SCL) - 16) / (2 * Prescaler)
    DDRC = 0X00;
    TWSR = 0x00;                        // Prescaler = 1
    TWBR = ((F_CPU / SCL_CLOCK) - 16) / 2;  // Bit rate register
    TWCR = (1 << TWEN);                // Enable TWI
}

void I2C_Start(void)
{
    TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);  // Send START
    while (!(TWCR & (1 << TWINT)));                    // Wait for TWINT flag
}

void I2C_Stop(void)
{
    TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);  // Send STOP
}

void I2C_Write(uint8_t data)
{
    TWDR = data;                                     // Load data
    TWCR = (1 << TWEN) | (1 << TWINT);               // Start transmission
    while (!(TWCR & (1 << TWINT)));                  // Wait for TWINT flag
}
