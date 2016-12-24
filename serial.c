/** 
 * @file serial.c 
 * UNIX Serial port device open/close for read()/write() to operate.
 * Setup serial port to blast bytes over a Unix file descriptor.
 *
 * @copyright
 * Copyright (C) 2016 Real Flight Systems
 * @author James F Dougherty <jfd@realflightsystems.com>
 */

/**
 * @defgroup serial serial
 * @addtogroup serial
 * @{
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>
#include <errno.h>

/* Local variables */
static struct termios  sio_tty;
static struct termios  sio_savetty;
static speed_t         sio_spd;

/**
 * @brief serial port open
 * 
 * Open the serial port device file (e.g. /dev/ttyUSB0) for read/write
 * at default 9600bps operational mode of Digole displays. Set
 * terminal characteristics for binary data and no HW flow control.
 * Save the current tty and HW com port attributes to be restored at 
 * shutdown via #serial_close 
 *
 * @param comport string value for the device file (e.g. "/dev/ttyUSB0")
 * @param highspeed when non-zero, the UART is opened at 115200baud
 */
int serial_open(char* comport, int highspeed) 
{
	int sfd = -1;
	int rc; 
	if ((sfd = open(comport, O_RDWR | O_NOCTTY | O_NONBLOCK)) < 0) { 
		syslog(LOG_DEBUG, "failed to open [%s]: %d, %s", 
		       comport, sfd, strerror(errno));
		return -1;
	}
	syslog(LOG_DEBUG, "opened sfd=%d for reading", sfd);
	if ((rc = tcgetattr(sfd, &sio_tty)) < 0) { 
		syslog(LOG_DEBUG, "failed to get attr: %d, %s", 
		       rc, strerror(errno));
		close(sfd);
		return rc;
	}
	sio_savetty = sio_tty; /* preserve original settings for restoration */
	
	if (highspeed)
	  	sio_spd = B115200;
	else
		sio_spd = B9600;

	cfsetospeed(&sio_tty, (speed_t)sio_spd);
	cfsetispeed(&sio_tty, (speed_t)sio_spd);
	
	cfmakeraw(&sio_tty);

	sio_tty.c_cc[VMIN] = 1;
	sio_tty.c_cc[VTIME] = 10;
	
	sio_tty.c_cflag &= ~CSTOPB;
	sio_tty.c_cflag &= ~CRTSCTS;    /* no HW flow control */
	sio_tty.c_cflag |= CLOCAL | CREAD;
	if ((rc = tcsetattr(sfd, TCSANOW, &sio_tty)) < 0) {
		syslog(LOG_DEBUG, "failed to set attr: %d, %s", 
		       rc, strerror(errno));
		close(sfd);
		return rc;
	}

	return sfd;
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
	tcsetattr(sfd, TCSANOW, &sio_savetty);
	close(sfd);
}

/** @}*/
