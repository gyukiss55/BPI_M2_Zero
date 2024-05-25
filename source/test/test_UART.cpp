// BPI_M2_ZERO_UART.cpp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

#include "BPI_M2_ZERO_UART.h"

int main(int argc, char* argv[])
{
    return testUART();
}
