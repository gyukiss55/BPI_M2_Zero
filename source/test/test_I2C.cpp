// BPI_M2_ZERO_I2C.cpp

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

#include "BPI_M2_ZERO_I2C.h"


int main(int argc, char *argv[])
{
    return testI2C(I2C_DEVICE, I2C_ADDR);
}
