#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

void TWI_Slave_Init(uint8_t slave_address);
void TWI_Slave_Transmit(uint8_t data);

int main(void) {
  
    DDRC = 0X00;
    TWI_Slave_Init(0xd0); // 7-bit slave address

    while (1) {
        // Wait for address + read request from master
        while (!(TWCR & (1 << TWINT))); // Wait for TWI interrupt
        while (!((TWSR & 0xF8) == 0xA8)) ; // SLA+R received, ACK sent
         
                TWI_Slave_Transmit('A'); // 1st byte
        

        while (!(TWCR & (1 << TWINT)));
        if ((TWSR & 0xF8) == 0xB8) { // Data transmitted, ACK received
            TWI_Slave_Transmit('B'); // 2nd byte
        }

        while (!(TWCR & (1 << TWINT)));
        if ((TWSR & 0xF8) == 0xB8) {
            TWI_Slave_Transmit('C'); // 3rd byte
        }

        // Wait for NACK
        while (!(TWCR & (1 << TWINT)));
        if ((TWSR & 0xF8) == 0xC0) {
            // Last byte transmitted, NACK received → done
            // Ready for next
        }

        // Clear interrupt and re-enable ACK
        TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
    }
}

void TWI_Slave_Init(uint8_t slave_address) {
    TWAR = slave_address; // Left shift for TWAR format
    TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT); // Enable TWI, ACK
}

void TWI_Slave_Transmit(uint8_t data) {
  
    TWDR = data; // Load data

    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA); // Clear INT, send with ACK
    
    
}
