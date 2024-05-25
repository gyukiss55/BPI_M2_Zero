// BPI_M2_ZERO_UART.h

#ifndef BPI_M2_ZERO_UART_H
#define BPI_M2_ZERO_UART_H

int uart_open(const char* portname);
int uart_set_interface_attribs(int fd, int speed);
void uart_close(int fd);
int uart_write(int fd, const char* data);
int uart_read(int fd, char* buf, int buf_len);
int testUART();

#endif

