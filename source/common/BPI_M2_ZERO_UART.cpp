// BPI_M2_ZERO_UART.cpp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

#include "BPI_M2_ZERO_UART.h"


int uart_open(const char* portname) {
    int fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        printf("Error %d opening %s: %s\n", errno, portname, strerror(errno));
        return -1;
    }
    return fd;
}

int uart_set_interface_attribs(int fd, int speed) {
    struct termios tty;
    if (tcgetattr(fd, &tty) != 0) {
        printf("Error %d from tcgetattr\n", errno);
        return -1;
    }

    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
    tty.c_iflag &= ~IGNBRK;         // disable break processing
    tty.c_lflag = 0;                // no signaling chars, no echo,
    // no canonical processing
    tty.c_oflag = 0;                // no remapping, no delays
    tty.c_cc[VMIN] = 1;            // read doesn't block
    tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

    tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
    // enable reading
    tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
    tty.c_cflag |= 0;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        printf("Error %d from tcsetattr\n", errno);
        return -1;
    }
    return 0;
}

void uart_close(int fd) {
    close(fd);
}

int uart_write (int fd, const char* data) {
    int len = strlen(data);
    int written = write(fd, data, len);
    if (written != len) {
        printf("Error %d from write\n", errno);
        return -1;
    }
    return 0;
}

int uart_read (int fd, char* buf, int buf_len) {
    int rdlen = read(fd, buf, buf_len - 1);
    if (rdlen > 0) {
        buf[rdlen] = '\0';
    }
    else if (rdlen < 0) {
        printf("Error %d from read\n", errno);
    }
    return rdlen;
}

int testUART () {
    const char* portname = "/dev/ttyS1"; // Adjust as per your UART port
    int fd = uart_open(portname);
    if (fd == -1) {
        return -1;
    }

    if (uart_set_interface_attribs(fd, B115200) == -1) {
        uart_close(fd);
        return -1;
    }

    char* send_data = "Hello UART\n";
    uart_write(fd, send_data);

    char recv_buf[100];
    int rdlen = uart_read(fd, recv_buf, sizeof(recv_buf));
    if (rdlen > 0) {
        printf("Received: %s\n", recv_buf);
    }

    uart_close(fd);
    return 0;
}
