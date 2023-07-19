/**
 * @brief imgload loads a startup byte-stream to the device 
 * 
 * Load start-up code
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>
#include "digole.h"
#include "serial.h"

int com_fd = -1;
extern int io_write(int fd, unsigned char* ptr, int nbytes);

//Builtin font ID: 6,10,18,51,120,123,0 (default)
//User font ID: 200,201,202,203
/* Startup for 2.4" DS320240CIPS-61TF2 - https://www.digole.com/index.php?productID=1212 */
char startup_screen[] = {
  'S','D',1,
  /* 
   * Command:CL, clear the screen panel.  : use current background
   * color to clear the screen.  This function also reset current font
   * to 0, screen rotation to 0, x position to 0, draw mode to ‘C’,
   * draw window to full screen, line pattern to 0xff.
   */
  'C','L',
  
  'S','F',120,

  'E','S','C',255,165,0,
  
   'T','P',12,1,'T','T','R','F','S','-','M','A','R','S','A', 0,
  'S','F',51,
  'E','S','C',0,100,100,
   'T','P',6,3,'T','T','G','R','O','U','N','D','S','T','A','T','I','O','N',0,
    'S','F',0,
  'E','S','C',255,255,255,
  'T','P',5,16,'T','T','C','o','p','y','r','i','g','h','t',' ', '(','C',')', ' ', '2','0','2','0','-','2','0','2','3',' ', 'R','F','S','-','M','A','R','S','A', 0
};
#define startup_screen_size (sizeof(startup_screen)/sizeof(startup_screen[0]))


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

#if 1
	/* 2.4" DS320240CIPS-61TF2 - https://www.digole.com/index.php?productID=1212 */
	dd_set_rot(1); /* NOTE: for TFT only, rotate 90 degrees */
	//bold font
	dd_setfont(18); //only 15 lines of text!!!
#endif

	/* Load startup screen */
	io_write(com_fd, startup_screen, startup_screen_size);
	
	/* Save/upload */
	dd_upload_start_screen2(startup_screen_size, startup_screen);
	
	/* Turn on start-screen */
	dd_display_startscreen(1);

	/* Turn off display config on boot */
	dd_display_config(0) ;
	dd_display_config(0) ;

	printf("Done\n");
	sleep(1);
	serial_close(com_fd);
	exit(0);

}
