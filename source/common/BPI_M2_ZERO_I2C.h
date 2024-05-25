// BPI_M2_ZERO_I2C.h

#ifndef BPI_M2_ZERO_I2C_H
#define BPI_M2_ZERO_I2C_H

#define I2C_DEVICE "/dev/i2c-0"  // Adjust the I2C bus number as needed
#define I2C_ADDR 0x68            // Replace with your device's I2C address

int i2c_write(int file, unsigned char reg, unsigned char value);
int i2c_read(int file, unsigned char reg, unsigned char* data);
int testI2C(const char* dev, int address);
int testI2C();

#endif
