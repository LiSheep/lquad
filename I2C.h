#ifndef I2C_H
#define I2C_H


extern uint8_t i2cWrite(uint8_t registerAddress, uint8_t *data, uint8_t length, bool sendStop);
extern uint8_t i2cWrite(uint8_t registerAddress, uint8_t data, bool sendStop);

extern uint8_t i2cRead(uint8_t registerAddress, uint8_t *data, uint8_t nbytes);
#endif