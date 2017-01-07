/**
 * @brief front instrument panel
 * 
 * Front instrument panel testing application
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

unsigned char buf[256];

#define N_COLORS 9
int colors[] = { RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PURPLE, WHITE, BLACK, 0};

unsigned char gps_icon_16x16[] = {
	0xff,0xff,0xcf,0xff,0x97,0xff,0x3b,0xff,0xbd,0xff,0xcd,0x7f,0xf2,0x3f,0xfc,0x3f,0xfc,0x47,0xf6,0xbb,0xd3,0xbd,0xad,0xdd,0x93,0xeb,0xcb,0xf3,0xf3,0xff,0xff,0xff };
#define gps_icon_size (sizeof(gps_icon_16x16)/sizeof(gps_icon_16x16[0]))


unsigned char batt_32x16[] = {
	0xe0,0x00,0x00,0x07,0xc0,0x00,0x00,0x03,0xcf,0xff,0xff,0xf3,0xcf,0xff,0xff,0xf3,0xcf,0xff,0xff,0xf3,0xcf,0xff,0xff,0xf1,0xcf,0xff,0xff,0xf0,0xcf,0xff,0xff,0xf0,0xcf,0xff,0xff,0xf0,0xcf,0xff,0xff,0xf0,0xcf,0xff,0xff,0xf3,0xcf,0xff,0xff,0xf3,0xcf,0xff,0xff,0xf3,0xcf,0xff,0xff,0xf3,0xc0,0x00,0x00,0x03,0xf0,0x00,0x00,0x0f};
#define batt_icon_size (sizeof(batt_32x16)/sizeof(batt_32x16[0]))

unsigned char batt_22x11[] = {

	0xff,0xff,0xf0
	,0x80,0x00,0x10
	,0x80,0x00,0x10
	,0x80,0x00,0x1c
	,0x80,0x00,0x1c
	,0x80,0x00,0x1c
	,0x80,0x00,0x1c
	,0x80,0x00,0x1c
	,0x80,0x00,0x10
	,0x80,0x00,0x10
	,0xff,0xff,0xf0

};
#define batt_22x11_size (sizeof(batt_22x11)/sizeof(batt_22x11[0]))

/*rfs logo 140x112 */
unsigned char rfs_image[]= { 

	'D','I','M',0x0a,0x00,0x8c,0x70,


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

};
#define rfs_img_size (sizeof(rfs_image)/sizeof(rfs_image[0]))



//	0, 14, 
char startup_screen[] = {
	'C','L','T','P',10,15,'T','T','H','e','e','l','o',0
};
#define su_size (sizeof(startup_screen)/sizeof(startup_screen[0]))


unsigned char fgcolor = GREEN;
unsigned char bgcolor = BLACK;


/* Dial offset for 0 degrees - change if screen flipped */
#define DEFAULT_DIAL_RADIUS (7.0)
#define OFFSET -90


void draw_degrees(char x, char y, char color)
{
	dd_set_printpos(x,y, 1);
	dd_setcolor(color);
	dd_draw_circle(x,y, 2, 0);
}

void update_dial(char cx, char cy, char radius,
		 unsigned char* old_x, unsigned char* old_y, 
		 unsigned handcolor, int degrees)
{


	char xa, ya;
	double angle, _x, _y, r;

	if (!old_x || !old_y)
		return;

	dd_set_printpos(cx,cy, 1);
	dd_setcolor(BLACK);
	dd_lineto(*old_x,*old_y);

	r = radius;
	angle = (M_PI/180) * (OFFSET + degrees);
	_x = cx + r * cos(angle);
	_y = cy + r * sin(angle);
	xa = (unsigned char)_x;
	ya = (unsigned char)_y;
	printf("x=%d, y=%d <%2.2f, %2.2f>\n",xa, ya, _x, _y); 

	dd_set_printpos(cx,cy, 1);
	dd_setcolor(handcolor);
	dd_lineto(xa,ya);


	*old_x = xa;
	*old_y = ya;
	
}

void init_dial(char* old_x, char* old_y, 
	       char cx, char cy, char radius, 
	       unsigned dialcolor, unsigned handcolor, 
	       int degrees)
{
	if (!old_x || !old_y)
		return;
	/* Draw dial - larger radii need a double circle */
	dd_setcolor(dialcolor);
	if (radius >= 16) { 
		dd_draw_circle(cx,cy, radius + 4, 0); /* radius + 4 */
		dd_draw_circle(cx,cy, radius + 3, 0); /* radius + 3 */
	}
	else { 
		dd_draw_circle(cx,cy, radius + 3, 0); /* radius + 4 */
	}

	/* Initially hand overwrites itself */
	*old_x = cx;
	*old_y = cy;
	update_dial(cx, cy, radius, old_x, old_y,  handcolor, degrees);
}


void space_pad3(char* buf, int value)
{
	if (value < 10){ 
		sprintf(buf, "  %d", value);
	}
	if (value >= 10 && value < 100){ 
		sprintf(buf,  " %d",value);
	}
	else if (value >= 100) {
		sprintf(buf, "%d", value);
	}
}


/*
 * draw_rssi: ch=4, rssi=10
 * dd_drawbox: x=42 y=100 w=1 h=0
 * 
 * draw_rssi: ch=5, rssi=0
 * dd_drawbox: x=45 y=90 w=1 h=10
 */

/* RSSI level settings */
#define RSSI_MAX_BAR_H 10


void draw_rssi(char x, char y, char chan, char strength)
{ 
	unsigned char d;

	if (strength > 10)
		strength = 10;

	d =  RSSI_MAX_BAR_H - strength;

	/* Clear old bar area */
	dd_setcolor(BLACK); 
	dd_draw_box(x + chan * 3, y, 1, RSSI_MAX_BAR_H);

	/* Set color based on strength */
	if (strength < 3)
		dd_setcolor(RED); 
	else if (strength >= 3 && strength <= 5)
		dd_setcolor(YELLOW);
	else if (strength > 5)
		dd_setcolor(GREEN);
	
	dd_draw_box(x + chan * 3, y + d, 1, RSSI_MAX_BAR_H - d);
}

/* 113 x 83 */
void battery_set_level (char x, char y, char color, char z )
{
	char i;

	dd_setcolor(BLACK);
	dd_draw_box(x,y, 13, 4);	

	if (z <= 0){
		z = 0;
		dd_setcolor(RED);
	}
	else if (z >= 1 && z <= 2)
		dd_setcolor(YELLOW);
	else if (z >= 3 && z <= 5)
		dd_setcolor(GREEN);

	if ( z >= 5 )
		z = 4;

	printf("level=%d\n", z);

	for (i = 0; i <= z; i++){
		dd_draw_box(x + 3*i, y, 1, 4);
	}

//	dd_setcolor(color);
//	dd_setfont(FONT1);
	sprintf(buf, "%3d%%", z == 0 ? 10 : (z+1)*20);
//	dd_draw_str((x+24)/4,(y+4)/6, buf);
	dd_draw_str(x/8+3,y/8 % 8 + 4, buf);
//	dd_setfont(FONT0);


#if 0
	dd_draw_box(113, 83, 1, 4);
	dd_draw_box(116, 83, 1, 4);
	dd_draw_box(119, 83, 1, 4);
	dd_draw_box(122, 83, 1, 4);
	dd_draw_box(125, 83, 1, 4);
//	dd_draw_box(111, 83, 1, 4);
//	dd_draw_box(111, 87, 1, 4);
#endif
}


void battery_meter_init(char* x, char* y, char* color, int level)
{
	if (!x || !y || !color)
		return;
	dd_setcolor(*color);
	draw_bitmap( *x, *y, 22, 11, batt_22x11);
	*x+=3;
	*y+=3;
	battery_set_level( *x, *y, *color, level);

}

/**
 * @brief main test application
 * 
 * Demo features of display driver.
 */
int main(int argc, char* argv[])
{
	int i = 0, j = 0;
	char xa, ya;
	char cx = 30, cy=110;
	char b1x, b1y, b1c, b2x, b2y, b2c;
	char s1x, s1y, s2x, s2y;
	int chan = 0;
	char dx, dy;
	double angle, r = DEFAULT_DIAL_RADIUS;
	char rssi;

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
	sleep(1);
	printf("Reopen as high-speed mode...\n");
	if ((com_fd = serial_open(argv[1],1)) < 0) { 
		printf("error: could not open [%s]\n", argv[1]);
		exit(2);
	}

	print("Running in 115Kbps mode\n");

#endif

	dd_set_mode('C');
	dd_set_printpos(0,0, 1);
	dd_set_printpos(0,0, 0);
	dd_clear_screen();	

	dd_setcolor(BLACK);
	dd_setbgcolor(BLACK);
	dd_setcolor(WHITE);

#if 0
	dd_setfont(FONT0);
	dd_draw_str(0, 0, "The quick brown fox jumps over the fence.");
	sleep(10);
	serial_close(com_fd);
	exit(0);
#endif

	dd_setcolor(bgcolor); /* black background */
	dd_setbgcolor(bgcolor);




#if 0
	/* Dashed line #1/2/3 */
	dd_setcolor(YELLOW); 
	dd_set_mode('X');
	dd_set_line_pattern(0x55);
	dd_hline(0,38, DISP_W);
	dd_hline(0,76, DISP_W);
#endif
	dd_setcolor(0xff); 
	dd_set_line_pattern(0xff);
	dd_set_mode('C');
	dd_setcolor(fgcolor); /* white foreground */

	/* Local GPS Position */
	dd_draw_str(0, 0, "N36.52 W120.07");

//	dd_setcolor(YELLOW); 
//	dd_draw_str(16, 0, " LCL");

	/* Local altitude and speed */
	dd_setcolor(fgcolor); 
	dd_draw_str(0, 1, " 195,000 ft 1235 mph");

	/* Local Brng to remote and distance */
	dd_draw_str(0, 2, "BRNG 137 SW 12.3 mi");

	/* Remote GPS Position */
	dd_draw_str(0, 3, "N40.85 W119.12");

	dd_setcolor(WHITE); 
	dd_draw_str(16,3, " RMT");

	/* Remote Altitude and speed */
	dd_setcolor(fgcolor); 
	dd_draw_str(0, 4, " 95,000 ft 435 mph");

	/* Local Brng to remote and distance */
	dd_draw_str(0, 5, "BRNG 180 NW 12.5 mi");


	/* Compass Labels */
	dd_draw_str(0, 7, " N          N  ");
	dd_draw_str(0, 8, "   N        N  ");

	cx = 11;
	cy = 114;
	dd_set_mode('C');
	/* Draw compass dial */
	init_dial(&dx, &dy, cx, cy, (char)r, BLUE, YELLOW, 0);

	dd_set_mode('C');

	draw_degrees(cx+40,cy-10, fgcolor);

//	dd_draw_box(30,BASE + 6,  1, 2);
//	dd_draw_box(30,BASE + 9,  1, 2);
//	dd_draw_box(30,BASE + 12, 1, 2);
//	dd_setcolor(WHITE);

#if 0
	draw_rssi(0,1);
	draw_rssi(1,2);
	draw_rssi(2,4);
	draw_rssi(3,8);
	draw_rssi(4,10);
	draw_rssi(5,0);
#endif


	for (i = 0; i < gps_icon_size; i++)
		gps_icon_16x16[i] = ~gps_icon_16x16[i];

#if 0
	for (i = 0; i < batt_icon_size; i++)
		battery_empty_48x24[i] = ~battery_empty_48x24[i];
	draw_bitmap(110, 80,48, 24, battery_empty_48x24);
#endif

//	for (i = 0; i < batt_24x12_size ; i++)
//		batt_24x12[i] = ~ batt_24x12[i];
//	draw_bitmap(110, 80, 22, 11, batt_22x11);

	b1x = 106; 
	b1y = 80;
	b1c = GREEN;
	battery_meter_init(&b1x, &b1y, &b1c, 5);
	b2x = 106; 
	b2y = 92;
	b2c = GREEN;
	battery_meter_init(&b2x, &b2y, &b2c, 5);

	s1x = 118;
	s1y = 0;
	s2x = 118;
	s1y = 40;

	while(1)
	for (i = 0; i < 360; i++) { 




		space_pad3(buf, i);
		dd_setcolor(fgcolor); 
		/* Local Brng to remote and distance */
		dd_draw_str(5, 2, buf);

		/* Update dial text and hand */
		space_pad3(buf,i);
		dd_setcolor(fgcolor); 
		/* Local Brng to remote and distance */
		dd_draw_str(3, 8, buf);

		update_dial(cx, cy, (char)r,&dx, &dy, YELLOW, i); 

		for (chan = 0; chan < 6; chan++) { 
			draw_rssi(s1x, s1y, chan, random() % 10);
			draw_rssi(s2x, s2y, chan, random() % 10);
		}

		if (1) {
			battery_set_level(b1x, b1y, b1c, random() % 6); /* 5 levels */
			battery_set_level(b2x, b2y, b2c, random() % 6); /* 5 levels */
		}
		dd_setcolor(WHITE);
		draw_bitmap(146, 0,16, 16, gps_icon_16x16);
//		ms_delay(25);
		ms_delay(500);
//		sleep(1);
	}

	dd_setcolor(WHITE);;
	serial_close(com_fd);
}
//
