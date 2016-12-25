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

#define N_COLORS 9
int colors[] = { RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PURPLE, WHITE, BLACK, 0};

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

	print("Running in 115Kbps mode\n");

	dd_setcolor(0); /* black background */
	dd_setbgcolor(0);
	dd_setcolor(0xff); /* white foreground */
#if 1
	/* TESTS */
	printf("Bitmap load testing\n");

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
	printf("Loading AMG Image (Monochrome) 160x128 - %d bytes\n", amg_img_size);
	draw_bitmap(0,0, 160, 128, &amg_img[8]);
	printf("done\n");
	sleep(5);

	/* 256 Color Mode */
	dd_set_mode('C');
	dd_set_printpos(0,0, 1);
	dd_clear_screen();	
	printf("Loading Black Cat Image (256 color) 128x128 - %d bytes\n",black_cat_img_size);
	dd_draw_bitmap256(16,0,128,128, &black_cat_img[8]);
	printf("done\n");
	sleep(5);

	/* 256 Color mode */
	dd_set_mode('C');
	dd_set_printpos(0,0, 1);
	dd_clear_screen();	
	printf("Loading Bahamas Image (256 color) 160x108 - %d bytes\n",img_256_size);
	dd_draw_bitmap256(0,0,160,108, &img_256[8]);
	printf("done\n");
	sleep(5);

	/* 262K color bitmap */
	dd_set_mode('C');
	dd_set_printpos(0,0, 1);
	dd_clear_screen();	
	printf("Loading Image (262K color) 128x128 - %d bytes\n",
	       img_262k_size);
	dd_draw_bitmap262K(16,0,128,128, &img_262k[8]);

	sleep(5);

	printf("2D testing\n");


	printf("Pixel testing\n");

	dd_set_mode('C');
	dd_set_printpos(0,0, 1);
	dd_clear_screen();	

	for (i = 0; i < DISP_W; i+=10)
		for(j = 0; j < DISP_H; j+=10){
			dd_setcolor(colors[i % 16]);
			dd_setpixel(i, j, colors[i% 16]);
		}

	printf("HLine test\n");
	dd_clear_screen();
	dd_set_printpos(0,0,1);
	for (i = 0; colors[i]; i++) { 
		for(j = 0; j < DISP_H; j+=2){
			dd_setcolor(colors[i]);
			dd_hline(0, j, DISP_W);
		}
	}
	sleep(1);
	printf("VLine test\n");
	dd_clear_screen();
	dd_set_printpos(0,0,1);
	for (i = 0; i < colors[i]; i++) { 
		for(j = 0; j < DISP_W; j+=2){
			dd_setcolor(colors[i]);
			dd_vline(j, 0, DISP_H);
		}
	}
	sleep(1);
	printf("VLine Test (Dotted/White)\n");
	dd_clear_screen();
	dd_set_printpos(0,0,1);
	dd_set_line_pattern(0x55);
	dd_setcolor(WHITE);

	for(j = 0; j < DISP_W; j+=2){
		dd_vline(j, 0, DISP_H);
	}
	sleep(2);
	printf("VLine Test (Dashed/Yellow)\n");
	dd_clear_screen();
	dd_set_printpos(0,0,1);
	dd_set_line_pattern(0xd7);
	dd_setcolor(YELLOW);
	for(j = 0; j < DISP_H; j+=2){
		dd_hline(0, j, DISP_W);
	}
	sleep(2);
	printf("Text Mode/Monochrome Color testing\n");
	dd_set_mode('C');
	dd_set_printpos(0,0, 1);
	dd_clear_screen();	
	i = 0;
	while(colors[i] != 0) { 
		dd_setcolor(colors[i]);
		dd_draw_box(0,0, 160, 128);

		dd_setbgcolor(colors[i % N_COLORS]);
		dd_setcolor(colors[i]);
		dd_draw_str(0, 0, "Hello World");
		dd_draw_str(0, 1, "This is a line 1");
		dd_draw_str(0, 2, "This is a line 2");
		dd_draw_str(0, 3, "This is a line 3");
		i++;
		sleep(1);
	}
#endif

	sleep(1);
	dd_clear_screen();
	dd_setcolor(0); /* black background */
	dd_setbgcolor(0);
	dd_setcolor(0xff); /* white foreground */
	/* Color cycle */

	i = 1;
	printf("Looping through colors forever... Press Ctrl-C to stop\n");
	while(1) { 
		i %= 256;
		dd_setcolor(i);
		dd_draw_str(0, 0, "The quick brown fox ");
		dd_draw_str(0, 1, "jumps over the lazy ");
		dd_draw_str(0, 2, "dog. Line #3        ");
		sprintf(buf, "Color %d 0x%02x          ", i, i);
		dd_draw_str(0, 3, buf);
		/* Circle pattern */
		dd_draw_box(0, 60, 60, 60);
		dd_setcolor(0);
		dd_draw_circle(30,90, 20, 1);
		dd_setcolor(i);
		dd_draw_circle(30,90, 10, 1);
		/* Hatch pattern */
		dd_set_line_pattern(0x55);
		for(j = 0; j < 60; j+=2){
			dd_vline(60+j, 60, 60);
		}
		dd_set_line_pattern(0xff);
		dd_setcolor(0);

		i++;
		sleep(1);
	}
	printf("Closing COM\n");
	serial_close(com_fd);
	return 0;
}
