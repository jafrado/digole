/**  mandel.c   by Eric R. Weeks   written 9-28-96
 **  weeks@physics.emory.edu
 **  http://www.physics.emory.edu/~weeks/
 **  
 **  This program is public domain, but this header must be left intact
 **  and unchanged.
 **  
 **  to compile:  cc -o mand mandel.c
 ** 
 **/

/**
 * Add Digole OLED library support - jfd
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "digole.h"

extern int serial_open(unsigned char* comport, int highspeed) ;
extern int writen(int fd, const unsigned char* ptr, int nbytes);
int colors[] = { RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PURPLE, WHITE, BLACK, 0};
#define N_COLORS 9

int com_fd = -1;                /* Com port file descriptor     */

int main(int argc, char* argv[])
{
	double x,xx,y,cx,cy;
	int iteration,hx,hy;
	int itermax = 100;		/* how many iterations to do	*/
	double magnify=1.0;		/* no magnification		*/
	int hxres = 160;		/* horizonal resolution		*/
	int hyres = 128;		/* vertical resolution		*/

	/* header for PPM output */
	printf("P6\n# CREATOR: Eric R Weeks / mandel program\n");
	printf("%d %d\n255\n",hxres,hyres);

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

	/* Init screen */
	dd_set_mode('C');
	dd_set_printpos(0,0, 1);
	dd_set_printpos(0,0, 0);
	dd_clear_screen();	


	for (hy=1;hy<=hyres;hy++)  {
		for (hx=1;hx<=hxres;hx++)  {
			cx = (((float)hx)/((float)hxres)-0.5)/magnify*3.0-0.7;
			cy = (((float)hy)/((float)hyres)-0.5)/magnify*3.0;
			x = 0.0; y = 0.0;
			for (iteration=1;iteration<itermax;iteration++)  {
				xx = x*x-y*y+cx;
				y = 2.0*x*y+cy;
				x = xx;
				if (x*x+y*y>100.0)  {
				  				  printf("x=%d,y=%d i=%d %2.2f\n", hx, hy, iteration, x*x+y*y);
				  break;
				}
			}
			dd_setcolor(colors[iteration % N_COLORS]);
			if (iteration < 90)  {
			  dd_setpixel(hx, hy, colors[iteration % N_COLORS] );
			}
			else {
			  dd_setpixel(hx, hy, RED);
			}

		}
	}
	printf("done\n");
	serial_close(com_fd);
}



