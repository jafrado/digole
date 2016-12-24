/** 
 * @file io.c 
 * IO abstraction routines based on read/write system calls to reliably read
 * and write some number of bytes over a Unix file descriptor.
 *
 * @copyright
 * Copyright (C) 2016 Real Flight Systems
 * @author James F Dougherty <jfd@realflightsystems.com>
 */

/**
 * @defgroup io io
 * @addtogroup io
 * @{
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <errno.h>
#include <unistd.h>
#include "digole.h"

static int byte_count = 0; /*!< For metering - every 64-bytes of data requires a 40ms delay from the host to avoid overwhelming the display controller */

/* NOTE: requires write()/read() for serial communications IO which
 * can be easily replaced with puts()/gets() at the lowest layer
 */

/** 
 * @brief write n bytes of data to a file descriptor
 *
 * On Linux, since write is not guaranteed to write all of the bytes
 * provided, we keep track of the number of bytes written and retry
 * sending the data as needed.
 * 
 * @param[in] fd the file descriptor to write to
 * @param[in] ptr the address of the data buffer to write
 * @param[in] nbytes the number of bytes to write
 * @return number of bytes successfully written
 */
int writen(int fd, unsigned char* ptr, int nbytes)
{
	int nleft, nwritten;
	nleft = nbytes;
	while (nleft > 0){
		nwritten = write(fd, ptr, nleft);
		byte_count += nwritten;
		if (nwritten <= 0)
			return(nwritten);               
		nleft -= nwritten;
		ptr += nwritten;
	}
#if 0
	/* rate limit for 9600 */
	if (!(byte_count % 64))
		delay(40);
#endif

    return(nbytes - nleft);
}

/** 
 * @brief read n bytes of data from a file descriptor
 *
 * On Linux, since read is not guaranteed to read all of the bytes
 * available in one call, we continously read the specified number of bytes
 * from the descriptor into the data buffer provided. 
 * 
 * @param[in] fd the file descriptor to read from
 * @param[in,out] ptr the address of the data buffer to read into 
 * @param[in] nbytes the number of bytes to read
 * @return number of bytes successfully read
 */
int readn(int fd, unsigned char* ptr, int nbytes)
{
	int nleft, nread;
	nleft = nbytes;
	while (nleft > 0) {
	top:
		nread = read(fd, ptr, nleft);
		if ((nread < 0) && (errno == EAGAIN)) { 
			errno = 0;
			goto top;
		}
		else if (nread < 0)
			return(nread);          	/* error, return < 0 */
		else if (nread == 0)
			break;                  	/* EOF */
		nleft -= nread;
		ptr += nread;
	}
	return(nbytes - nleft);         	/* return >= 0 */
}

/** @}*/
