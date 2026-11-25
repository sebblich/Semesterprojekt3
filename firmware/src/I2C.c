#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>


/* I2C */
void i2c_init(void)  { TWSR1 = 0; TWBR1 = 72; }                 

void i2c_start(void) {
    TWCR1 = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR1 & (1 << TWINT)));
}
void i2c_stop(void) {
    TWCR1 = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    _delay_us(10);
}
void i2c_write(uint8_t data) {
    TWDR1 = data;
    TWCR1 = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR1 & (1 << TWINT)));
}
uint8_t i2c_read(uint8_t ack) {              
    TWCR1 = (1 << TWINT) | (1 << TWEN) | (ack ? (1 << TWEA) : 0);
    while (!(TWCR1 & (1 << TWINT)));
    return TWDR1;
}

/* two helpers for sensors that have registers */
void reg_write(uint8_t addr, uint8_t reg, uint8_t val) {
    i2c_start();
    i2c_write(addr << 1);                    
    i2c_write(reg);
    i2c_write(val);
    i2c_stop();
}
uint8_t reg_read(uint8_t addr, uint8_t reg) {
    i2c_start();
    i2c_write(addr << 1);
    i2c_write(reg);
    i2c_start();                             
    i2c_write((addr << 1) | 1);              
    uint8_t v = i2c_read(0);
    i2c_stop();
    return v;
}