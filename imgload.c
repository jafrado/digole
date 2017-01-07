/**
 * @brief imgload loads a bitmap into the startup screen area
 * 
 * Load start-up bitmap
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>
#include "digole.h"

int com_fd = -1;

extern int serial_open(unsigned char* comport, int highspeed) ;
extern int io_write(int fd, const unsigned char* ptr, int nbytes);

/*rfs logo 140x112 - doc/realflightsystems_sm_140x112.jpg 
* Uploaded to here:
*
* At 140*112/8 or 1960 pixels we can do a full size monochrome bitmap
* 
*/
unsigned char rfs_image[]= { 
//	'C','L','T','P',10,20,'T','T','F','i','r','m','w','a','r','e', ' ', '1','.','0',0,
	'D','I','M',0x0a,0x00,0x8c,0x70,
#if 0
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0c,0x1f,0xf8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xcc,0x1f,0xfc,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0xcc,0x1c,0x60,0x03,0x80,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0x0c,0x1c,0x60,0x07,0xe0,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x06,0x30,0x0f,0xf8,0x60,0x07,0xfe,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x07,0x70,0x0f,0xf8,0x60,0x06,0x3f,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x07,0x71,0xef,0xf8,0x60,0x06,0x04,0xc0,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x03,0x31,0xfe,0x18,0x60,0x07,0x80,0xe0,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x03,0xb0,0x3e,0x18,0x60,0x03,0xf0,0xe0,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x38,0x03,0xb8,0x7e,0x18,0x60,0x00,0x78,0xe1,0x80,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x98,0x01,0xdf,0xf6,0x08,0x40,0x08,0x18,0xe7,0xc0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x01,0xdc,0x01,0xcf,0xe0,0x00,0x00,0x0f,0x38,0xff,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x03,0xcc,0x00,0xc7,0x00,0x00,0x00,0x0f,0xf8,0x7c,0x38,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x07,0x0e,0x00,0xe0,0x00,0x00,0x00,0x01,0xf0,0x70,0x7c,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x1e,0x17,0x0e,0x00,0x00,0x00,0x00,0x00,0x00,0xe0,0xff,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x18,0x73,0xfe,0x00,0x00,0x00,0x00,0x00,0x01,0xc0,0xe7,0x80,0x00,0x00,0x00
,0x00,0x00,0x00,0x18,0xf1,0xf0,0x00,0x00,0x00,0x3c,0x00,0x01,0x80,0xe1,0xc0,0x00,0x00,0x00
,0x00,0x00,0x00,0x1b,0xc0,0x40,0x00,0x00,0x00,0x3e,0x80,0x00,0x80,0x78,0xe0,0x00,0x00,0x00
,0x00,0x00,0x00,0x1f,0x80,0x00,0x00,0x00,0x00,0x1d,0xa0,0x00,0x00,0x3c,0x10,0x00,0x00,0x00
,0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x00,0x00,0x01,0x78,0x00,0x03,0x1e,0x38,0x00,0x00,0x00
,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x7c,0x00,0x07,0x86,0x1c,0x00,0x00,0x00
,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x1c,0x00,0x01,0xce,0x1e,0x00,0x00,0x00
,0x00,0x00,0x00,0x03,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfc,0x3f,0x00,0x00,0x00
,0x00,0x00,0x00,0x01,0x80,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x3c,0x7b,0x80,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0xf1,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3e,0x3e,0x00,0x00,0x00,0x00,0x01,0xe0,0x40,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0x01,0xc0,0x00,0x00,0x00,0x03,0xc1,0xe0,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x71,0xff,0xc0,0x00,0x03,0x83,0xf0,0x00,0x00
,0x00,0x03,0x00,0x60,0x00,0x00,0x04,0x00,0x00,0x7e,0x00,0x3c,0x00,0x00,0x07,0x38,0x00,0x00
,0x00,0x07,0x80,0xe0,0x00,0x00,0x18,0x00,0x03,0x83,0x00,0x03,0x00,0x00,0x1f,0x1c,0x00,0x00
,0x00,0x01,0xe1,0xc0,0x00,0x00,0x30,0x00,0x18,0x00,0x80,0x00,0xc0,0x00,0x1b,0x9c,0x00,0x00
,0x00,0x00,0xf3,0x80,0x00,0x00,0x60,0x00,0x60,0x00,0x40,0x00,0x20,0x00,0x19,0xce,0x00,0x00
,0x00,0x00,0x3f,0x80,0x00,0x00,0xc0,0x01,0x80,0x00,0x30,0x00,0x18,0x00,0x18,0xc6,0x00,0x00
,0x00,0x00,0x1e,0x00,0x00,0x00,0x80,0x02,0x00,0x00,0x18,0x00,0x0c,0x00,0x1c,0xe0,0x00,0x00
,0x00,0x3f,0x00,0x00,0x00,0x01,0x00,0x0c,0x00,0x00,0x0c,0x00,0x00,0x00,0x0c,0x60,0x00,0x00
,0x00,0x3f,0xf0,0x00,0x00,0x03,0x00,0x20,0x00,0x00,0x02,0x00,0x02,0x00,0x0e,0x07,0x80,0x00
,0x00,0x77,0xfc,0x00,0x00,0x02,0x00,0xc0,0x00,0x00,0x01,0x00,0x01,0x00,0x07,0x1f,0xc0,0x00
,0x00,0x78,0x18,0x00,0x00,0x02,0x01,0x03,0xf8,0x03,0xf0,0x80,0x00,0x00,0x02,0x7c,0xc0,0x00
,0x00,0x38,0x00,0x00,0x00,0x04,0x02,0x3c,0x00,0x00,0x0f,0xc0,0x00,0x80,0x00,0xf1,0xc0,0x00
,0x00,0x1e,0x00,0x00,0x00,0x04,0x0f,0x80,0x00,0x00,0x00,0x70,0x00,0xc0,0x01,0xe3,0xc0,0x00
,0x00,0x0e,0x00,0x00,0x00,0x08,0x1c,0x00,0x00,0x00,0x00,0x3e,0x00,0x40,0x00,0x87,0x80,0x00
,0x00,0x07,0x80,0x00,0x00,0x08,0x60,0x00,0x00,0x00,0x00,0x11,0x80,0x40,0x00,0x0f,0x00,0x00
,0x03,0x03,0xc0,0x00,0x00,0x0b,0xc0,0x00,0x00,0x00,0x00,0x08,0x30,0x20,0x00,0x1c,0x00,0x00
,0x03,0x01,0xc0,0x00,0x00,0x1c,0x80,0x00,0x00,0x00,0x00,0x04,0x0c,0x20,0x00,0x38,0x78,0x00
,0x03,0x38,0xc0,0x00,0x00,0x39,0x00,0x00,0x00,0x00,0x00,0x04,0x03,0x20,0x00,0x33,0xf8,0x00
,0x07,0x31,0x00,0x00,0x00,0x72,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0xa0,0x00,0x3f,0xdc,0x00
,0x06,0x33,0x80,0x00,0x00,0x94,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x1f,0x1c,0x00
,0x0e,0x63,0x00,0x00,0x03,0x18,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x30,0x00,0x08,0x3c,0x00
,0x0e,0x67,0x00,0x00,0x06,0x10,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x38,0x00,0x00,0x78,0x00
,0x0e,0xe7,0x00,0x00,0x0c,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x26,0x00,0x01,0xe0,0x00
,0x0f,0xe6,0x00,0x00,0x18,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x22,0x00,0x07,0xc0,0x00
,0x03,0xfe,0x00,0x00,0x30,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x21,0x00,0x0f,0x0c,0x00
,0x00,0x3c,0x00,0x00,0x60,0xa0,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x80,0x0c,0x3e,0x00
,0x0e,0x00,0x00,0x00,0xc1,0x20,0x00,0x00,0x47,0xc8,0x00,0x00,0x20,0x20,0x40,0x00,0x3f,0x00
,0x1f,0x00,0x00,0x00,0x81,0x20,0x00,0x01,0xfc,0xc4,0x00,0x00,0x10,0x20,0x60,0x06,0x33,0x00
,0x1f,0x9c,0x00,0x01,0x02,0x20,0x00,0x00,0xfd,0x43,0x00,0x00,0x10,0x20,0x20,0x06,0x33,0x00
,0x19,0xb8,0x00,0x01,0x02,0x20,0x00,0x00,0xfb,0x01,0x80,0x00,0x08,0x40,0x10,0x07,0x33,0x00
,0x31,0xf0,0x00,0x02,0x04,0x20,0x00,0x01,0xfb,0x80,0xc0,0x00,0x08,0x40,0x10,0x07,0x33,0x00
,0x33,0xe0,0x00,0x02,0x0c,0x20,0x00,0x03,0xf7,0x80,0xc0,0x00,0x00,0x40,0x10,0x07,0x33,0x80
,0x33,0xe0,0x00,0x02,0x08,0x20,0x00,0x03,0xff,0x00,0x60,0x00,0x00,0xc0,0x08,0x03,0x31,0x80
,0x33,0xc0,0x00,0x04,0x10,0x20,0x00,0x03,0xfe,0x00,0x70,0x00,0x04,0x80,0x08,0x03,0xf1,0x80
,0x33,0xf8,0x00,0x04,0x10,0x00,0x00,0x03,0xfc,0x00,0x70,0x00,0x04,0x80,0x08,0x01,0xe0,0x00
,0x31,0xf8,0x00,0x04,0x30,0x10,0x00,0x01,0xf8,0x00,0x78,0x00,0x05,0x00,0x04,0x00,0x00,0x00
,0x00,0x00,0x00,0x04,0x20,0x10,0x00,0x00,0xc0,0x00,0x38,0x00,0x03,0x00,0x04,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x20,0x10,0x00,0x00,0x80,0x00,0x38,0x00,0x02,0x00,0x04,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x40,0x10,0x00,0x00,0x61,0x00,0x78,0x00,0x02,0x00,0x04,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x40,0x10,0x00,0x00,0x10,0x00,0x78,0x00,0x02,0x00,0x04,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0xc0,0x18,0x00,0x00,0x01,0x80,0x70,0x00,0x06,0x00,0x04,0x00,0x00,0x00
,0x00,0x00,0x00,0x04,0x80,0x08,0x00,0x00,0x03,0xf0,0xf0,0x00,0x01,0x00,0x04,0x00,0x00,0x00
,0x00,0x00,0x00,0x04,0x80,0x08,0x00,0x00,0x03,0xf8,0xf0,0x00,0x09,0x00,0x04,0x00,0x00,0x00
,0x00,0x00,0x00,0x04,0x80,0x00,0x00,0x00,0x07,0xff,0xf0,0x00,0x11,0x00,0x08,0x00,0x00,0x00
,0x00,0x00,0x00,0x04,0x80,0x00,0x00,0x00,0x07,0xff,0xf0,0x00,0x11,0x00,0x08,0x00,0x00,0x00
,0x00,0x00,0x00,0x04,0x00,0x04,0x00,0x00,0x03,0xff,0xe0,0x00,0x21,0x00,0x08,0x00,0x00,0x00
,0x00,0x00,0x06,0x03,0x00,0x04,0x00,0x00,0x03,0xff,0xe0,0x00,0x41,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x0e,0x03,0x00,0x00,0x00,0x00,0x01,0xff,0xc0,0x00,0xc1,0x00,0x10,0x00,0x00,0x00
,0x00,0x00,0x07,0x01,0x00,0x00,0x00,0x00,0x01,0xff,0x80,0x00,0x81,0x00,0x10,0x00,0x00,0x00
,0x00,0x00,0x07,0x09,0x00,0x02,0x00,0x06,0x01,0xff,0x00,0x01,0x00,0x00,0x20,0x00,0x00,0x00
,0x00,0x00,0x02,0x01,0x80,0x02,0x00,0x03,0xff,0xfe,0x00,0x02,0x00,0x00,0x20,0x00,0x00,0x00
,0x00,0x00,0x03,0x11,0x80,0x01,0x00,0x00,0xff,0xfc,0x00,0x04,0x00,0x00,0x40,0x00,0x00,0x00
,0x00,0x00,0x07,0x31,0xc0,0x01,0x00,0x00,0x7f,0xf0,0x00,0x0c,0x01,0x00,0xc0,0x00,0x00,0x00
,0x00,0x00,0x02,0x01,0x20,0x00,0x80,0x00,0x01,0x00,0x00,0x18,0x01,0x01,0x80,0x00,0x00,0x00
,0x00,0x00,0x01,0x81,0x30,0x00,0x80,0x00,0x00,0x00,0x00,0x30,0x01,0x01,0x00,0x00,0x00,0x00
,0x00,0x00,0x03,0x80,0x18,0x00,0x40,0x00,0x00,0x00,0x00,0x40,0x01,0x06,0x00,0x00,0x00,0x00
,0x00,0x00,0x01,0x80,0x84,0x00,0x40,0x00,0x00,0x00,0x00,0x80,0x01,0x0c,0x00,0x00,0x00,0x00
,0x00,0x00,0x01,0xc0,0x82,0x00,0x20,0x00,0x00,0x00,0x01,0x00,0x01,0x18,0x00,0x00,0x00,0x00
,0x00,0x00,0x01,0x00,0x81,0x80,0x10,0x00,0x00,0x00,0x02,0x00,0x01,0x20,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x40,0xc0,0x10,0x00,0x00,0x00,0x04,0x00,0x01,0xc0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x40,0x30,0x08,0x00,0x00,0x00,0x18,0x00,0x03,0x80,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x20,0x18,0x08,0x00,0x00,0x00,0x20,0x00,0x07,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x30,0x06,0x04,0x00,0x00,0x00,0xc0,0x00,0x1a,0x40,0xc0,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x10,0x01,0xc2,0x00,0x00,0x01,0x00,0x00,0x62,0x81,0xe0,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x08,0x00,0x32,0x00,0x00,0x06,0x00,0x03,0x80,0x13,0xc0,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x04,0x00,0x07,0x00,0x00,0x18,0x00,0x1c,0x04,0x43,0x80,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x02,0x00,0x01,0xe0,0x00,0x60,0x01,0xe0,0x04,0x0d,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x01,0x80,0x00,0x5f,0x81,0x80,0x3e,0x00,0x04,0x06,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0xc0,0x00,0x60,0xff,0xff,0xc0,0x00,0x08,0x1e,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x10,0x70,0x00,0x00,0x00,0x08,0x38,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x07,0x80,0x1f,0x80,0x00,0x00,0x00,0x10,0x78,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0xec,0x00,0x00,0x00,0x00,0x20,0x70,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x20,0x20,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0e,0x00,0x00,0x0c,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x80,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x00,0x60,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1e,0x03,0x80,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xf8,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
#else


#if 1
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x0f,0xfc,0x7f,0xc3,0xfe,0x1f,0x00,0x0f,0xf9,0xf0,0x7c,0x7f,0xe3,0xe7,0xff,0xfc,0x00
,0x00,0x1f,0xfe,0x7f,0x83,0xfe,0x1e,0x00,0x0f,0xf1,0xe0,0x78,0xff,0xf3,0xcf,0xff,0xf8,0x00
,0x00,0x1f,0xfe,0xff,0x87,0xfe,0x3e,0x00,0x1f,0xf3,0xe0,0xf9,0xff,0xf7,0xcf,0xff,0xf8,0x00
,0x00,0x3e,0x7c,0xf8,0x00,0x3c,0x3e,0x00,0x1f,0x03,0xe0,0xf1,0xf0,0x07,0x9f,0x0f,0x80,0x00
,0x00,0x3e,0x7d,0xf0,0x00,0x3c,0x7c,0x00,0x1f,0x07,0xc1,0xf1,0xf0,0x0f,0x9f,0x0f,0x80,0x00
,0x00,0x7f,0xf9,0xff,0x0f,0xfc,0x7c,0x00,0x3f,0xe7,0xc1,0xf3,0xef,0xcf,0xff,0x0f,0x00,0x00
,0x00,0x7f,0xfb,0xfe,0x1f,0x7c,0xf8,0x00,0x3f,0xcf,0x83,0xe3,0xef,0xdf,0xfe,0x1f,0x00,0x00
,0x00,0xff,0xf3,0xfe,0x3e,0x78,0xf8,0x00,0x7f,0xcf,0x83,0xe7,0xdf,0x9f,0xfe,0x1e,0x00,0x00
,0x00,0xf9,0xe3,0xc0,0x7e,0xf8,0xf0,0x00,0x7c,0x0f,0x07,0xc7,0xcf,0x9e,0x7c,0x3e,0x00,0x00
,0x01,0xf1,0xe7,0xc0,0x7c,0xf9,0xf0,0x00,0xf8,0x1f,0x07,0xcf,0x8f,0x3e,0x7c,0x3e,0x00,0x00
,0x01,0xf3,0xe7,0xc0,0xf8,0xf9,0xf0,0x00,0xf8,0x1f,0x07,0x8f,0x9f,0x3c,0xf8,0x7c,0x00,0x00
,0x03,0xe3,0xcf,0xf9,0xff,0xf3,0xfe,0x01,0xf0,0x3f,0xef,0x9f,0xff,0x7c,0xf8,0x7c,0x00,0x00
,0x03,0xe3,0xcf,0xf3,0xff,0xf3,0xfc,0x01,0xf0,0x3f,0xcf,0x9f,0xfe,0x7c,0xf0,0x78,0x00,0x00
,0x07,0xe7,0x9f,0xf7,0xff,0xf7,0xfc,0x03,0xe0,0x7f,0xdf,0x0f,0xfc,0xf9,0xf0,0xf8,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x3f,0xc3,0xe7,0xcf,0xf3,0xff,0xdf,0xf3,0xff,0xfe,0x1f,0xe0,0x00,0x00,0x00
,0x00,0x00,0x00,0x3f,0xc3,0xcf,0x8f,0xf3,0xff,0x9f,0xe3,0xff,0xff,0x1f,0xe0,0x00,0x00,0x00
,0x00,0x00,0x00,0x7f,0x87,0xcf,0x9f,0xe7,0xff,0xbf,0xe7,0xff,0xff,0x3f,0xc0,0x00,0x00,0x00
,0x00,0x00,0x00,0x70,0x07,0xcf,0x1c,0x00,0xf8,0x3e,0x07,0x9f,0x3e,0x38,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0xf8,0x0f,0x9f,0x3e,0x00,0xf8,0x7c,0x0f,0x9e,0x3e,0x7c,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0xfe,0x0f,0x9f,0x3f,0x80,0xf0,0x7f,0xcf,0x3e,0x7c,0x7f,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0xff,0x9f,0xfe,0x3f,0xe1,0xf0,0xff,0x9f,0x3e,0x7c,0x7f,0xc0,0x00,0x00,0x00
,0x00,0x00,0x00,0x3f,0x9f,0xfe,0x0f,0xe1,0xe0,0xff,0x9f,0x3c,0xf8,0x1f,0xc0,0x00,0x00,0x00
,0x00,0x00,0x00,0x0f,0x8f,0xfc,0x03,0xe3,0xe0,0xf0,0x1e,0x7c,0xf8,0x07,0xc0,0x00,0x00,0x00
,0x00,0x00,0x00,0x07,0x00,0x7c,0x01,0xc3,0xe1,0xf0,0x3e,0x79,0xf0,0x03,0x80,0x00,0x00,0x00
,0x00,0x00,0x00,0x0f,0x00,0x78,0x03,0xc7,0xc1,0xf0,0x3c,0xf9,0xf0,0x07,0x80,0x00,0x00,0x00
,0x00,0x00,0x07,0xfe,0x7f,0xf9,0xff,0x87,0xc3,0xfe,0x7c,0xf3,0xe3,0xff,0x00,0x00,0x00,0x00
,0x00,0x00,0x07,0xfe,0x7f,0xf1,0xff,0x87,0x83,0xfc,0x7c,0xf3,0xe3,0xff,0x00,0x00,0x00,0x00
,0x00,0x00,0x0f,0xfc,0xff,0xe3,0xff,0x0f,0x87,0xfc,0xf9,0xe7,0xe7,0xfe,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x07,0xf0,0x7e,0x3f,0x1f,0x9f,0x9f,0xe3,0xf3,0xfd,0xef,0xf3,0xfc,0x0f,0xe0,0x3e,0x00
,0x00,0x0f,0xf0,0xfe,0x7e,0x3f,0x3f,0x3f,0xc7,0xf7,0xf9,0xdf,0xf3,0xfc,0x1f,0xe0,0x7c,0x00
,0x00,0x0e,0xf0,0x0e,0xf0,0x38,0x78,0x0f,0x00,0x71,0xe3,0xdc,0xe7,0xb8,0x01,0xe0,0x3c,0x00
,0x00,0x1e,0xe0,0x1c,0xf0,0x78,0x78,0x0e,0x00,0xe1,0xc3,0xbc,0xe7,0x38,0x03,0xc0,0x38,0x00
,0x00,0x1f,0xe1,0xfc,0xfc,0x7e,0x7e,0x1e,0x0f,0xe3,0xc7,0xb9,0xef,0x78,0x07,0xc0,0x78,0x00
,0x00,0x3f,0xc3,0xdc,0x1e,0x7c,0x0f,0x1c,0x1e,0xe3,0x87,0x79,0xce,0x70,0x0f,0x80,0x70,0x00
,0x00,0x39,0xc7,0xbc,0x0e,0xe0,0x07,0x1c,0x3d,0xe3,0x87,0x73,0xce,0xf0,0x1e,0x00,0x70,0x00
,0x00,0x79,0x8f,0x38,0x1c,0xe0,0x0e,0x38,0x79,0xc7,0x0e,0x73,0x9c,0xe0,0x78,0x00,0xf0,0x00
,0x00,0x7f,0x9f,0xfb,0xfc,0xf9,0xfe,0x38,0xff,0xc7,0x0e,0xff,0x9c,0xe0,0x7f,0x9e,0xe0,0x00
,0x00,0xff,0x3f,0xff,0xf9,0xf3,0xfc,0x79,0xff,0xcf,0x1c,0xff,0x3d,0xc0,0xff,0x3d,0xe0,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
#else
	/* Year of the commercial drone */

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x3c,0x7f,0x1e,0x01,0xe1,0xc1,0x9f,0xc0,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x7e,0x7f,0x3f,0x03,0xf3,0xe7,0x9f,0xc0,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0xe3,0x40,0x63,0x03,0x32,0x65,0x81,0x80,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0xc0,0xc0,0x60,0x00,0x36,0x61,0x01,0x80,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x01,0x80,0xfe,0x78,0x00,0x76,0x63,0x03,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x01,0x80,0xfe,0x1e,0x00,0x64,0x63,0x06,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x01,0x80,0xc0,0x07,0x01,0xc4,0x63,0x06,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x01,0x80,0xc0,0x03,0x03,0x84,0x43,0x0c,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x01,0xc6,0x80,0xc3,0x03,0x04,0xc3,0x0c,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0xfc,0xfe,0xfe,0x07,0xe7,0xdf,0x98,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x79,0xfe,0x7c,0x07,0xe3,0x9f,0x98,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x61,0x9f,0xc3,0x87,0xe0,0x0f,0x0f,0xc1,0xfe,0xc3,0x7f,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x21,0x9f,0xc3,0x87,0xf0,0x1f,0x8f,0xc1,0xfe,0xc2,0x7f,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x33,0x10,0x03,0x84,0x30,0x31,0xc8,0x00,0x30,0x82,0x40,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x36,0x30,0x06,0x8c,0x30,0x30,0xd8,0x00,0x21,0x86,0xc0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x1e,0x3f,0x84,0x8c,0x30,0x60,0xd8,0x00,0x61,0xfe,0xfe,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x1c,0x3f,0x8c,0xcf,0xe0,0x60,0xdf,0x80,0x61,0xfe,0xfe,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x18,0x30,0x0f,0xcf,0xc0,0x60,0xdf,0x80,0x61,0x86,0xc0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x18,0x30,0x1f,0xcc,0xc0,0x61,0x98,0x00,0x61,0x84,0xc0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x18,0x20,0x18,0xc8,0xc0,0x73,0x90,0x00,0x61,0x04,0x80,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x18,0x3f,0xb0,0xc8,0x60,0x3f,0x10,0x00,0x41,0x0c,0xfe,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x18,0x7f,0xb0,0xd8,0x60,0x1e,0x30,0x00,0xc3,0x0d,0xfe,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x1e,0x0f,0x0e,0x39,0xc7,0x3f,0x9f,0x83,0xc6,0x1c,0x30,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x3f,0x1f,0x8e,0x39,0xc7,0x3f,0x9f,0xc7,0xe6,0x1c,0x30,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x71,0xb1,0xce,0x39,0xc7,0x20,0x10,0xce,0x34,0x1c,0x20,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x60,0x30,0xde,0x7b,0xcf,0x60,0x30,0xcc,0x0c,0x34,0x60,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0xc0,0x60,0xda,0x53,0x4a,0x7f,0x30,0xd8,0x0c,0x24,0x60,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0xc0,0x60,0xda,0xd3,0x5a,0x7f,0x3f,0x98,0x0c,0x66,0x60,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0xc0,0x60,0xda,0xb3,0x56,0x60,0x3f,0x18,0x0c,0x7e,0x60,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0xc0,0x61,0x93,0xb2,0x76,0x60,0x33,0x18,0x0c,0xfe,0x60,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0xe3,0x73,0x93,0x32,0x66,0x40,0x23,0x1c,0x78,0xc6,0x40,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x7e,0x3f,0x13,0x32,0x66,0x7f,0x21,0x8f,0xd9,0x86,0x7e,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x3c,0x1e,0x33,0x26,0x64,0xff,0x61,0x87,0x99,0x86,0xfe,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x18,0x63,0x83,0xc0,0x10,0x3e,0x1f,0x83,0xc3,0x0d,0xfc,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x18,0x43,0x87,0xe0,0x10,0x3f,0x1f,0xc7,0xe3,0x89,0xfc,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x18,0xc3,0x8c,0x60,0x30,0x23,0x90,0xcc,0x73,0x89,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x10,0xc6,0x8c,0x00,0x30,0x61,0xb0,0xcc,0x36,0x8b,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x30,0xc4,0x8f,0x00,0x20,0x61,0xb0,0xd8,0x36,0x9b,0xf8,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x30,0xcc,0xc3,0xc0,0x60,0x61,0xbf,0x98,0x36,0xdb,0xf8,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x30,0xcf,0xc0,0xe0,0x60,0x61,0xbf,0x18,0x36,0xdb,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x30,0x9f,0xc0,0x60,0x40,0x63,0x33,0x18,0x64,0x53,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x39,0x98,0xd8,0x60,0xc0,0x47,0x23,0x1c,0xe4,0x72,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x1f,0xb0,0xdf,0xc0,0xc0,0x7e,0x21,0x8f,0xcc,0x73,0xf8,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x0e,0x30,0xcf,0x80,0x80,0xfc,0x61,0x87,0x8c,0x37,0xf8,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00


#endif

#endif
};
#define rfs_img_size (sizeof(rfs_image)/sizeof(rfs_image[0]))

/* Test screen */
char startup_screen[] = {
	'C','L','T','P',10,15,'T','T','H','e','l','l','o',0
};
#define su_size (sizeof(startup_screen)/sizeof(startup_screen[0]))


/**
 * @brief main test application
 * 
 * Load image into startup screen
 */
int main(int argc, char* argv[])
{
	int i;
	if (argc != 2) { 
		printf ("usage: %s <comport> (e.g. /dev/ttyUSB0) \n", argv[0]);
		exit(1);
	}
	if ((com_fd = serial_open(argv[1],0)) < 0) { 
		printf("error: could not open [%s]\n", argv[1]);
		exit(2);
	}
#ifndef __arm__
	/* Open com port at 9600, send baud-switch command and goto 115Kbaud*/
	printf("Set Baud to 115200\n");
	/* Set high-speed UART mode */
	io_write(com_fd, "SB115200\0",9);
	close(com_fd);
	com_fd = -1;
	sleep(1);
	printf("Reopen as high-speed mode...\n");
	if ((com_fd = serial_open(argv[1],1)) < 0) { 
		printf("error: could not open [%s]\n", argv[1]);
		exit(2);
	}
#endif /* !__arm__ */

	print("Running in 115Kbps mode\n");
	dd_set_mode('C');
	dd_set_printpos(0,0, 1);
	dd_set_printpos(0,0, 0);
	dd_clear_screen();	

	dd_setcolor(BLACK);
	dd_setbgcolor(BLACK);
	dd_setcolor(WHITE);


	/* Logo - sometimes you may want to invert it ... */
//	for (i = 0; i < rfs_img_size; i++)
//		rfs_image[i] = ~rfs_image[i];

	draw_bitmap(10, 0, 140, 112, &rfs_image[8]);
	dd_upload_start_screen(rfs_img_size, rfs_image);

	/* Turn on start-screen */
	dd_display_startscreen(1);

	/* Turn off display config */
	dd_display_config(0) ;
	dd_display_config(0) ;

	printf("Done\n");
	sleep(1);
	serial_close(com_fd);
	exit(0);

}