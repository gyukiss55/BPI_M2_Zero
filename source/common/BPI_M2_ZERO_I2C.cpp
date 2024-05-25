// BPI_M2_ZERO_I2C.cpp

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

#include "BPI_M2_ZERO_I2C.h"


int i2c_write(int file, unsigned char reg, unsigned char value)
{
    unsigned char buf[2];
    buf[0] = reg;
    buf[1] = value;

    if (write(file, buf, 2) != 2) {
        perror("Failed to write to the i2c bus");
        return -1;
    }
    return 0;
}

int i2c_read(int file, unsigned char reg, unsigned char* data)
{
    if (write(file, &reg, 1) != 1) {
        perror("Failed to write to the i2c bus");
        return -1;
    }

    if (read(file, data, 1) != 1) {
        perror("Failed to read from the i2c bus");
        return -1;
    }
    return 0;
}

int testI2C (const char* dev, int address)
{
    int file;
    char* filename = (char*)dev;

    // Open the I2C device
    if ((file = open(filename, O_RDWR)) < 0) {
        perror("Failed to open the i2c bus");
        exit(1);
    }

    // Specify the I2C address of the device we want to communicate with
    if (ioctl(file, I2C_SLAVE, address) < 0) {
        perror("Failed to acquire bus access and/or talk to slave");
        exit(1);
    }

    // Example: Write to a register
    unsigned char reg = 0x00;   // Replace with the register you want to write to
    unsigned char value = 0x12; // Replace with the value you want to write
    if (i2c_write(file, reg, value) < 0) {
        exit(1);
    }

    // Example: Read from a register
    unsigned char read_data;
    if (i2c_read(file, reg, &read_data) < 0) {
        exit(1);
    }

    printf("Read value: 0x%02x\n", read_data);

    // Close the I2C device
    close(file);

    return 0;
}


int testI2C()
{
    return testI2C(I2C_DEVICE, I2C_ADDR);
}
