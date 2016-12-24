#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "digole.h"

int com_fd = -1;

extern int serial_open(unsigned char* comport, int highspeed) ;
extern int writen(int fd, const unsigned char* ptr, int nbytes);
/* amg_img.c */
extern unsigned char amg_img[];
extern int amg_img_size;

/* black_cat_img.c */
extern unsigned char black_cat_img[];
extern int black_cat_img_size;

/* img_262k.c */
extern unsigned char img_262k[];
extern int img_262k_size;

/* img_262k.c */
extern unsigned char img_256[];
extern int img_256_size;

/* img_compass.c */
extern unsigned char img_compass[];
extern int img_compass_size;

/**
 * @brief main test application
 * 
 * Demo features of display driver.
 */
int main(int argc, char* argv[])
{
	int i = 0, j = 0;
	unsigned char buf[256];

	if (argc != 2) { 
		printf ("usage: %s <comport> (e.g. /dev/ttyUSB0) \n", argv[0]);
		exit(1);
	}
	if ((com_fd = serial_open(argv[1],0)) < 0) { 
		printf("error: could not open [%s]\n", argv[1]);
		exit(2);
	}

	/* Open com port at 9600, send baud-switch command and goto 115Kbaud*/

	printf("Set Baud to 115200\n");
	/* Set high-speed UART mode */
	writen(com_fd, "SB115200\0",9);
	close(com_fd);
	sleep(1);
	printf("Reopen as high-speed mode...\n");
	if ((com_fd = serial_open(argv[1],1)) < 0) { 
		printf("error: could not open [%s]\n", argv[1]);
		exit(2);
	}


	int colors[] = { 0xe4, 0x43, 0xe2, 0x7c, 0x5f, 0xfc, 0xff, 0};

#if 1

	/* Monochrome Bitmap */
	dd_set_mode('C');
	dd_set_printpos(0,0, 1);
	dd_set_printpos(0,0, 0);
	dd_clear_screen();	
	printf("Loading Compass Image (Monochrome) 84x84 - %d bytes\n",
	      img_compass_size);
	draw_bitmap(0,0, 84, 84, &img_compass[8]);
	printf("done\n");
	sleep(5);

	dd_set_mode('C');
	dd_set_printpos(0,0, 1);
	dd_set_printpos(0,0, 0);
	dd_clear_screen();	
	printf("Loading AMG Image (Monochrome) 160x128 - %d bytes\n",
	       amg_img_size);
	draw_bitmap(0,0, 160, 128, &amg_img[8]);
	printf("done\n");
	sleep(5);

	dd_set_mode('C');
	dd_set_printpos(0,0, 1);
	dd_clear_screen();	

	printf("Loading Black Cat Image (256 color) 128x128 - %d bytes\n",
	       black_cat_img_size);

	dd_draw_bitmap256(16,0,128,128, &black_cat_img[8]);
	printf("done\n");
	sleep(5);


	printf("Loading Bahamas Image (256 color) 160x108 - %d bytes\n",
	       img_256_size);

	dd_draw_bitmap256(0,0,160,108, &img_256[8]);
	printf("done\n");
	sleep(5);


	dd_set_mode('C');
	dd_set_printpos(0,0, 1);
	dd_clear_screen();	

	printf("Loading Image (262K color) 128x128 - %d bytes\n",
	       img_262k_size);
	dd_draw_bitmap262K(16,0,128,128, &img_262k[8]);


#if 0
	dd_set_mode('C');
	dd_set_printpos(0,0, 1);
	dd_clear_screen();	

	for (i = 0; i < DISP_W; i+=10)
		for(j = 0; j < DISP_H; j+=10){
			dd_setcolor(colors[i % 16]);
			dd_setpixel(i, j, colors[i% 16]);
		}

	dd_set_mode('C');
	dd_set_printpos(0,0, 1);
	dd_clear_screen();	

	i = 0;
	while(colors[i] != 0) { 
		dd_setcolor(colors[i]);
		dd_draw_box(0,0, 160, 128);

		dd_setbgcolor(colors[i+1]);
		dd_setcolor(colors[i]);
		dd_draw_str(0, 0, "Hello World");
		dd_draw_str(0, 1, "This is a line 1");
		dd_draw_str(0, 2, "This is a line 2");
		dd_draw_str(0, 3, "This is a line 3");
		i++;

		sleep(1);
	}
#endif




#else
	dd_clear_screen();
//	dd_set_mode(_TEXT_);
	i = 0;

	while(1) { 
		i %= 256;
		dd_setcolor(i);
//		dd_setbgcolor(0+i);
		dd_draw_str(0, 0, "Hello World");
		sprintf(buf, "Color %d 0x%02x\n", i, i);
		dd_draw_str(0, 1, buf);
		dd_draw_str(0, 2, "This is a line 2");
		dd_draw_str(0, 3, "This is a line 3");
		i++;
		sleep(1);
	}
#endif

	serial_close(com_fd);
	return 0;
}
