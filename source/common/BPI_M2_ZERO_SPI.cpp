// BPI_M2_ZERO_SPI.cpp


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#define SPI_DEVICE "/dev/spidev0.0"
#define SPI_MODE SPI_MODE_0
#define SPI_BITS_PER_WORD 8
#define SPI_SPEED 500000

#include "BPI_M2_ZERO_SPI.h"


int testSPI() {
    int spi_fd;
    int ret;
    uint8_t tx[] = { 0xDE, 0xAD, 0xBE, 0xEF }; // Example data to send
    uint8_t rx[sizeof(tx)] = { 0, };

    // Open SPI device
    spi_fd = open(SPI_DEVICE, O_RDWR);
    if (spi_fd < 0) {
        perror("Failed to open SPI device");
        exit(EXIT_FAILURE);
    }

    // Set SPI mode
    ret = ioctl(spi_fd, SPI_IOC_WR_MODE, &SPI_MODE);
    if (ret == -1) {
        perror("Failed to set SPI mode");
        close(spi_fd);
        exit(EXIT_FAILURE);
    }

    // Set bits per word
    ret = ioctl(spi_fd, SPI_IOC_WR_BITS_PER_WORD, &SPI_BITS_PER_WORD);
    if (ret == -1) {
        perror("Failed to set bits per word");
        close(spi_fd);
        exit(EXIT_FAILURE);
    }

    // Set max speed
    ret = ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &SPI_SPEED);
    if (ret == -1) {
        perror("Failed to set max speed");
        close(spi_fd);
        exit(EXIT_FAILURE);
    }

    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long)tx,
        .rx_buf = (unsigned long)rx,
        .len = sizeof(tx),
        .speed_hz = SPI_SPEED,
        .delay_usecs = 0,
        .bits_per_word = SPI_BITS_PER_WORD,
    };

    // Perform SPI transaction
    ret = ioctl(spi_fd, SPI_IOC_MESSAGE(1), &tr);
    if (ret < 1) {
        perror("Failed to perform SPI transaction");
        close(spi_fd);
        exit(EXIT_FAILURE);
    }

    // Print received data
    for (int i = 0; i < sizeof(rx); i++) {
        printf("Received: 0x%02X\n", rx[i]);
    }

    // Close SPI device
    close(spi_fd);

    return 0;
}
