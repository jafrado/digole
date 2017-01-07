/** 
 * @file rpi_spi.c 
 * Raspberry Pi Linux SPI Driver for r/w IO using Linux SPI driver
 * Setup SPI port on Raspberry Pi to blast bytes over SPI device descriptor.
 *
 * @copyright
 * Copyright (C) 2017 Real Flight Systems
 * @author James F Dougherty <jfd@realflightsystems.com>
 */

/**
 * @defgroup serial serial
 * @addtogroup serial
 * @{
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <syslog.h>
#include <errno.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

static const char *device = "/dev/spidev0.0";

/*
 * mode knobs
 * SPI_LOOP|SPI_CPHA|SPI_CPOL|SPI_LSB_FIRST|SPI_CS_HIGH|SPI_3WIRE|
 * SPI_NO_CS|SPI_READY
 */
uint8_t spi_mode;
uint8_t spi_bits = 8;
uint32_t spi_speed = 200000;
/* doesn't seem to work at any higher speed ... (sigh) */
//uint32_t spi_speed = 1953000;
uint16_t spi_delay;

/**
 * @brief serial port open
 * 
 * Open the SPI evice file (e.g. /dev/spidev0.0) for read/write
 * at default 9600bps operational mode of Digole displays. Set
 * terminal characteristics for binary data and no HW flow control.
 * Save the current tty and HW com port attributes to be restored at 
 * shutdown via #serial_close 
 *
 * @param device string value for the device file (e.g. "/dev/spidev0.0")
 * @param highspeed ignored
 */
int serial_open(char* device, int highspeed) 
{
	int fd = -1;
	int ret; 
	fd = open(device, O_RDWR);
	if (fd < 0) { 
		printf("device not found[%s]\n", device);
		return fd; 
	}
	/*
	 * spi mode
	 */
	ret = ioctl(fd, SPI_IOC_WR_MODE, &spi_mode);
	if (ret == -1){
		printf("%s:can't set spi mode\n", device);
		return -1;
	}
	ret = ioctl(fd, SPI_IOC_RD_MODE, &spi_mode);
	if (ret == -1){ 
		printf("%s:can't get spi mode\n", device);
		return -2;
	}
	/*
	 * bits per word
	 */
	ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &spi_bits);
	if (ret == -1) { 
		printf("%s:can't set bits per word\n", device);
		return -3;
	}
	ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &spi_bits);
	if (ret == -1) {
		printf("%s:can't get bits per word\n", device);
		return -4;
	}

	/*
	 * max speed hz
	 */
	ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &spi_speed);
	if (ret == -1) { 
		printf("%s:can't set max speed hz [%d]\n", device, spi_speed);
		return -5;
	}
	ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &spi_speed);
	if (ret == -1){
		printf("%s:can't get max speed hz\n", device);
		return -6; 
	}

	printf("%s: spi mode: %d, bits per word %d, speed=%d (%d Khz)\n", 
	       device, spi_mode, spi_bits, spi_speed, spi_speed/1000);

	return fd;
}

/**
 * @brief serial port close
 * 
 * Close the serial port file descriptor and restore terminal and HW
 * com port to their original settings.
 *
 * @param sfd serial file descriptor returned from #serial_open
 */
void serial_close(int sfd)
{	
	close(sfd);
}

/** @}*/
