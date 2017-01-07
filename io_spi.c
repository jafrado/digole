/** 
 * @file io.c 
 * IO abstraction routines for Linux SPI Driver interface
 *
 * @copyright
 * Copyright (C) 2017 Real Flight Systems
 * @author James F Dougherty <jfd@realflightsystems.com>
 */

/**
 * @defgroup io io
 * @addtogroup io
 * @{
 */


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#include "digole.h"

/* rpi_spi.c */
extern uint8_t spi_mode;
extern uint8_t spi_bits;
extern uint32_t spi_speed;
extern uint16_t spi_delay;

/** 
 * @brief write n bytes of data to a file descriptor
 *
 * @param[in] fd the file descriptor to write to
 * @param[in] ptr the address of the data buffer to write
 * @param[in] nbytes the number of bytes to write
 * @return number of bytes successfully written
 */
int io_write(int fd, unsigned char* ptr, int nbytes)
{
	int ret;
	struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long)ptr,
		.rx_buf = (unsigned long)NULL,
		.len = nbytes,
		.delay_usecs = spi_delay,
		.speed_hz = spi_speed,
		.bits_per_word = spi_bits,
	};

	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 1) { 
		printf("error:can't send spi message: %d\n", ret);
	}
	return nbytes;
}

/** 
 * @brief read n bytes of data from a file descriptor
 *
 * @param[in] fd the file descriptor to read from
 * @param[in,out] ptr the address of the data buffer to read into 
 * @param[in] nbytes the number of bytes to read
 * @return number of bytes successfully read
 */
int io_read(int fd, unsigned char* ptr, int nbytes)
{

	int ret;
	struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long)NULL,
		.rx_buf = (unsigned long)ptr,
		.len = nbytes,
		.delay_usecs = spi_delay,
		.speed_hz = spi_speed,
		.bits_per_word = spi_bits,
	};

	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 1) { 
		printf("error:can't send spi message: %d\n", ret);
	}
	return nbytes;
}

/** @}*/
