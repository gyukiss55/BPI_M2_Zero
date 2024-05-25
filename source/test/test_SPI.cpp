// BPI_M2_ZERO_SPI.cpp


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>


#include "BPI_M2_ZERO_SPI.h"


int main(int argc, char* argv[])
{
	return testSPI();
}