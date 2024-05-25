#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

#include "BPI_M2_ZERO_TCPIP.h"

int main(int argc, char* argv[])
{
    if (argc > 1)
        return TCPIP_Client(argv[1]);

    return TCPIP_Server();
}
