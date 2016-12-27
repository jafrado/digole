/** 
 * @mainpage Display Driver for Digole OLED Displays
 * 
 * @section intro Introduction
 *
 * This module implements Text and Graphics functionality for the Digole
 * Serial OLED Display modules made by <a href="http://www.digole.com/"> Digole </A>.
 * Tested and verified with Digole 1.8" Serial: UART/I2C/SPI True
 * Color OLED160x128 OLED Module DS160128COLED-46
 * 
 * @section platform Platform Support
 * 
 * For testing and initial bringup, the core library runs on Linux via
 * USB Serial and only 3 wires (TXD, VCC, GND) are soldered to the
 * module. Pinout is defined as below: <p> 
 * <ul><li> Black - Ground (connect to ground on OLED module)
 * <li> Brown - CTS
 * <li> Red - VCC (3V model used - connect to VCC on OLED module) 
 * <li> Orange - TXD (connect to Data on OLED module)
 * <li> Yellow - RXD (not currently used - may be in the future)
 * <li> Green - RTS
 * </ul> 
 * For more information on the FTDI USB->Serial Adapter Cable, see also:
 * http://www.ftdichip.com/Support/Documents/DataSheets/Cables/DS_TTL-232R_CABLES.pdf
 * <p>
 * 
 * The Digole HW module is setup as below. Pin-out for the module is
 * from the Digole HW Adapter manual:<p>
 * <img border=0 width=640 height=326 src="../../doc/hw_setup_ttl2323v3.jpg">
 * <p>
 * 
 * Relevant porting files and API's are defined in platform.h and the
 * implementation for Linux in platform_linux.c
 *<p>
 *
 * @section Test Application
 * 
 * A test application is provided to verify the functionality. Additional
 * utilities and test applications may be provided in the future.
 * 
 * @section ref Reference
 * See also: http://www.digole.com/index.php?productID=859 <p>
 * See also: http://www.digole.com//images/file/Tech_Data/Digole_Serial_Display_Adapter-Manual.pdf<p>
 *
 * @copyright
 * Copyright (C) 2016 Real Flight Systems
 * @author James F Dougherty <jfd@realflightsystems.com>
 * 
 *
 */
#ifndef  __DIGOLE_DISPLAY_H
#define  __DIGOLE_DISPLAY_H

/* Need to implement writen() in io.c and print_com() in digole.c */

/**
 * @defgroup display display 
 * @addtogroup display
 * @headerfile digole.h "digole.h"
 * @{
 */


/**
 * @brief - basic color palette
 */
enum COLORS{
	CYAN     = 0x5B,
	RED      = 0xE4,
	ORANGE   = 0xEC,
	PURPLE   = 0x66,
	MAGENTA  = 0xA1,
	YELLOW   = 0xFC,
	WHITE    = 0xFF,
	BLACK    = 0x00,
	GREEN    = 0x3C,
	BLUE     = 0x03,
	PEACH    = 0xF1,
	GREY     = 0x52
};

enum CGFONTS{
	FONT0 = 0,   /* u8g_font_unifont */
	FONT1 = 6,   /* u8g_font_4x6 */
	FONT2 = 10,  /* u8g_font_6x10 */
	FONT3 = 18,  /* u8g_font_9x18B */
	FONT4 = 51,  /* u8g_font_osr18 */
	FONT5 = 120, /* u8g_font_gdr20 */
	FONT6 = 123  /* u8g_font_osr35n */
};


/* Change for your Display */
#define DISP_W  (160)  /*!< screen \a width in pixels */
#define DISP_H  (128)  /*!< screen \a height in pixels */

/* IO delay routines - will need to be provided by your platform */

/** 
 * @brief microsecond delay
 * 
 *  Delay specified number of microseconds, the processor will wait
 *  this amount of time before continuing execution.
 * 
 * @param[in] usecs the number of microseconds to sleep
 */
void us_delay(unsigned int usecs);

/** 
 * @brief millisecond delay
 * 
 *  Delay specified number of milliseconds, the processor will wait
 *  this amount of time before continuing execution.
 * 
 * @param[in] usecs the number of milliseconds to sleep
 */
void ms_delay(unsigned int usecs);
/** 
 * @def delay(x) 
 * delays for \a x milliseconds 
 */
#define delay ms_delay
/*!< This is the delay value needed for loading 262K color bmp */
#define INTERNAL_DELAY    (800)

/*!< Defined when using Serial or SPI communication interface on module */
#define USE_DIGOLE_SERIAL_SPI 

/** 
 * @def print(x) 
 * output string data \a x to display
 */
#define print(x) print_com(com_fd, (x))
#define preprint() print("TT")

/** 
 * @def dd_set_rot90() 
 * Rotate orientation of display 90 degrees
 */
#define dd_set_rot90() print("SD1")
/** 
 * @def dd_set_rot180() 
 * Rotate orientation of display 180 degrees
 */

#define dd_set_rot180() print("SD2")
/** 
 * @def dd_set_rot270() 
 * Rotate orientation of display 270 degrees
 */

#define dd_set_rot_270() print("SD3")
/** 
 * @def dd_undo_rot() 
 * Restore orientation of display rotation to normal defaults
 */
#define dd_undo_rot() print("SD0")


/** 
 * @brief Print a line of text. 
 * 
 *  Print one line of null-terminated text. The current cursor
 *  position is automatically advanced to the next location.
 * 
 * @param[in] v the string to output
 */
void dd_println(unsigned char* v) ;

/** 
 * @brief Disable cursor
 * 
 * Disable the HW cursor
 */
void dd_disable_cursor(void) ;
/** 
 * @brief Enable cursor
 * 
 * Enable the HW cursor
 */
void dd_enable_cursor(void) ;

/** 
 * @brief Draw string 
 * 
 * Draws a string at specified x/y location where (0,0) is the origin 
 * and the display framebuffer extends to (DISP_W,DISP_H). Note that
 * the display will require different values for x/y to offset depending
 * on which font is loaded.
 * 
 * @param[in] x the x position 
 * @param[in] y the y position 
 * @param[in] s the string to display
 */
void dd_draw_str(unsigned char x, unsigned char y, unsigned char *s) ;

/** 
 * @brief Setting Drawing Position
 * 
 * Set the current drawing position for text or graphics mode. When
 * resetting both the graphics and text drawing positions this routine
 * should be called twice, once for graphics and another time for
 * text.
 * 
 * @param[in] x the x position 
 * @param[in] y the y position 
 * @param[in] graph when non-zero will reset the graphics drawing position, otherwise the text drawing position will be modified. 
 */
void dd_set_printpos(unsigned char x, unsigned char y, unsigned char graph);

/** 
 * @brief Clear Screen
 * 
 * Clear display and present empty framebuffer
 */
void dd_clear_screen(void) ;

/** 
 * @brief Set number of columns and rows for text-mode
 * 
 * This routine will configure the universal character LCD adapter
 * with the STCR command. Note that this routine is not needed for 
 * normal operational mode.
 * @param[in] col the number of columns
 * @param[in] rows the number of rows
 */
void dd_set_lcd_colrow(unsigned char col, unsigned char row) ;

/** 
 * @brief Display the display configuration on boot
 * 
 * This is an enable/disable to show the OLED display configuration
 * at power-up/boot.
 * 
 * @param[in] v when non-zero, will program the controller to show
 * display configuration on power-up/boot
 */
void dd_display_config(unsigned char v) ;
/** 
 * @brief Display the start screen on power-up/boot
 * 
 * This is an enable/disable to show the start-up screen on boot.
 * The start-up screen can be programmed to the display memory.
 * 
 * @param[in] m when non-zero, will program the controller to show
 * startup screen on power-up/boot.
 */
void dd_display_startscreen(unsigned char m) ;

/** 
 * @brief Set the Display Drawing Mode
 * 
 * This is a command (DM) to the display controller which takes a
 * single byte specifying the drawing mode. The command byte is
 * defined as only the following letters {C,|,!,~,&,^}. Where the
 * meaning of the drawing mode is defined as one of the 6 modes
 * available defined below:<p>
 * 
 * <ol><li> 'C'- Copy mode, it doesn’t matter what pixels exist on the
 * screen;this mode uses the current foreground color to over write
 * the pixel. For text displayed in any variant of the TT command, it
 * will also clear the character box to the background color. Note
 * that all other modes will not clear the character box.</li>
 * 
 * <li> ‘|’ - OR the current foreground color with the existing pixel.</li>
 * <li> ‘!’ - NOT - invert the color of the current pixel.</li>
 * <li> ‘&’ - AND the current foreground color with the existing pixel.</li>
 * <li> ‘^’ - XOR the current foreground color with the existing pixel.</li>
 * <li> ANY - Note that using any other letter will default to over-write mode
 * (like 'C') except the character box will not be cleared when using
 * text commands via the TT command. This is recommended to display text on a picture.
 * 
 * @param[in] m mode character as described above
 */
void dd_set_mode(unsigned char m);

/** 
 * @brief Set text position back one character (BS)
 * 
 * This virtual backspace allows you to repeatedly update one character
 */
void dd_set_text_pos_back(void);
/** 
 * @brief Adjust the current text position by specified offset
 * 
 * This command will add the specified x/y offsets to the controllers
 * internal HW cursor position to adjust the cursor position by the 
 * specified offsets.
 * 
 * @param[in] xoffset displacement (positive or negative) in the x plane
 * @param[in] yoffset displacement (positive or negative) in the y plane
 */
void dd_set_text_pos_offset(unsigned char xoffset, unsigned char yoffset);

/** 
 * @brief Adjust the current text position to absolute offset
 * 
 * Move HW text cursor to the the specified x/y offsets
 * 
 * @param[in] xoffset displacement from 0-DISP_W
 * @param[in] yoffset displacement from 0-DIP_H
 */
void dd_set_text_pos_abs(unsigned char x, unsigned char y);

/**
 * @brief Set the line pattern for line drawing operations
 * 
 * This command allows you to specify a byte which represents a
 * bitmask for drawing operations to affect the line drawing style.
 * When line-drawing operations are performed, the display controller
 * will repeat every 8 bits represented in the line pattern to allow
 * programming a configurable dotted or dashed line style (the
 * internal operation is an AND function as bits which are zero will
 * not be displayed).
 * 
 * <ul><li> 0x55 - draws a dotted line (0b01010101) 
 * <li> 0xd7 - draws a dashed line (0b11010111)</ul>
 * 
 * @param[in] pattern the byte value representing the bitmap
 */
void dd_set_line_pattern(unsigned char pattern);

/**
 * @brief digital port output
 * 
 * This command sends a byte out of the digital port.  It is largely
 * undocumented, the reference only says "Send a Byte to output head
 * on board, the current driving ability for each pin is: 25mA
 * (Sink/Source)"
 */
void dd_digital_output(unsigned char x);

/**
 * @brief Draw monochrome bitmap
 * 
 * This routine draws a black & white image at the specified x,y
 * coordinates.  Note that the image is represented in 1bpp format and
 * is affected by the foreground color and drawing mode (e.g. you can
 * set a different foreground color before drawing and make a
 * different color image).
 * 
 * @param[in] x the top left x coordinate for where to draw the bitmap
 * @param[in] y the top left y coordinate for where to draw the bitmap
 * @param[in] w the width of the bitmap
 * @param[in] h the height of the bitmap
 * @param[in] bitmap image data (...d...), each bit represent a pixel
 * in the image. Data in one byte can’t cross different lines, that
 * means, if the width of image is 12 pixels, you need 2 bytes for
 * each line. The MSB is on the left side.
 * <p> NOTE: the current graphics HW cursor positin (CGP) is unchanged.
 */
void draw_bitmap(unsigned char x, unsigned char y,unsigned char w, unsigned char h, unsigned char* bitmap) ;

/**
 * @brief Set display rotation
 * 
 * Set's the display rotation to one of the four specified angles
 * @param[in] d - angle setting (one of the below)
 * <ul><li> 0 - unchanged
 * <li> 1 - 90 degrees rotation
 * <li> 2 - 180 degrees rotation
 * <li> 3 - 270 degrees rotation
 * </ul>
 * NOTE that this setting affects the display, not the currently defined
 * drawing region.
 * 
 */
void dd_set_rot(unsigned char d) ;

/**
 * @brief set the display contrast
 * 
 * This command sets the display contrast but is only supported on displays
 * which have the ST7565 LCD Controller
 * 
 * @param[in] c the contrast value (0-255)
 */
void dd_set_contrast(unsigned char c) ;

/**
 * @brief draw a box
 * 
 * This command draws a filled rectangle at the specified x,y coordinate
 * with the specified width and height.
 * The current drawing color is used to draw the box.
 * 
 * @param[in] x the x position
 * @param[in] y the y position
 * @param[in] w the width of the box
 * @param[in] h the height of the box
 * 
 */
void dd_draw_box(unsigned char x, unsigned char y, unsigned char w, unsigned char h) ;
/**
 * @brief draw a circle
 * 
 * Draws a circle (optionally) filled at specified x,y coordinate
 * with specified radius.
 * 
 * @param x the x coordinate
 * @param y the y coordinate
 * @param r the radius (in pixels)
 * @param f whether to fill with foreground (current drawing) color
 */
void dd_draw_circle(int8_t x, unsigned char y, unsigned char r, unsigned char f);

/**
 * @brief draw a frame (rectangle) 
 * 
 * This routine will draw a rectangle at the specified x,y coordinate
 * with the specified width and height.
 * 
 * @param x the x coordinate
 * @param y the y coordinate
 * @param w the width of the rectangle
 * @param h the height of the rectangle
 */
void dd_draw_frame(unsigned char x, unsigned char y, unsigned char w, unsigned char h) ;

/**
 * @brief set a pixel a specified color
 * 
 * This routine sets a pixel at the provided x,y coordinate to the specified
 * color value.
 *
 * @param x the x coordinate
 * @param y the y coordinate
 * @param color the color value
 */
void dd_setpixel(unsigned char x, unsigned char y, unsigned char color) ;

/**
 * @brief draw a line
 * 
 * This routine will draw a line from x,y to x1,y1 using the currently
 * specified color and graphics position. When the line is done drawing
 * the current graphics position is updated to x1,y1.
 * 
 * @param x the starting x coordinate
 * @param y the starting y coordinate
 * @param x1 the ending x coordinate
 * @param y1 the ending y coordinate
 */
void dd_drawline(unsigned char x, unsigned char y, unsigned char x1, unsigned char y1) ;

/**
 * @brief draw a line from the current position to a new position
 * 
 * This routine will draw a line from the current position (last
 * graphics position x,y) to a new position using the currently
 * specified color. When the line is done drawing the current graphics
 * position is updated to x1,y1.
 * 
 * @param x the ending x coordinate
 * @param y the ending y coordinate
 */
void dd_lineto(unsigned char x, unsigned char y);

/**
 * @brief draw a horizontal line at specified position and width
 * 
 * This routine will draw a horizontal line from the specified position
 * using the specified width. When the line is done drawing the current 
 * graphics position is updated to x+w,y.
 * 
 * @param x the x coordinate
 * @param y the y coordinate
 * @param w the width of the line
 */
void dd_hline(unsigned char x, unsigned char y, unsigned char w);

/**
 * @brief draw a vertical line at specified position and height
 * 
 * This routine will draw a vertical line from the specified position
 * using the specified height. When the line is done drawing the current 
 * graphics position is updated to x,y+h.
 * 
 * @param x the x coordinate
 * @param y the y coordinate
 * @param h the height of the line
 */
void dd_vline(unsigned char x, unsigned char y, unsigned char h);
/**
 * @brief move text cursor to new line
 * 
 * This routine moves the text cursor to the next printable line
 */
void dd_next_text_line(void) ;
/**
 * @brief set the font to be used from preloaded flash locations
 * 
 * This routine sets which character set should be loaded from the
 * Character graphics ram (CGRAM). The RAM is implemented as FLASH
 * and font graphics can be saved into user defined regions. 
 * 
 * @param font the font to use -preloaded font #'s are(6,10,18,51,120,123, and 0(default)); user font #'s are (200,201,202,203) maps to 4 user fonts
 */
void dd_setfont(unsigned char font) ;
/**
 * @brief set the drawing color
 * 
 * This routine will set the color (0/1) for monochrome or (0-255) for
 * color displays.
 *
 * The color table is defined as below for 255 (indexed) color mode and
 * can be found <a href="http://www.digole.com/tools/256ColorCode.php"> here </a><p>
 *
 * 
 */
void dd_setcolor(unsigned char color) ;
/**
 * @brief set the current color as the background color
 * 
 * This routine will set the current (foreground) color
 * to the background color.
 * 
 * The color table is defined as below for 255 (indexed) color mode and
 * can be found <a href="http://www.digole.com/tools/256ColorCode.php"> here </a><p>
 *
 * @param color the color to set
 */
void dd_setbgcolor(unsigned char color) ;

/**
 * @brief turn on backlight
 */
void dd_backlight_on(void) ;
/**
 * @brief turn off backlight
 */
void dd_backlight_off(void);
/**
 * @brief turn on screen
 */
void dd_set_screen_on(void) ;
/**
 * @brief turn off screen
 */
void dd_set_screen_off(void) ;

/**
 * @brief send direct command to display
 * 
 * Send a direct command to the display and bypass the display controller.
 * @param[in] d data command byte to transmit
 */
void dd_direct_command(unsigned char d) ;


/**
 * @brief send direct data to display
 * 
 * Send direct data to the display and bypass the display controller.
 * @param[in] d data byte to transmit
 */
void dd_direct_data(unsigned char d) ;
/**
 * @brief move screen memory area from one location to another
 * 
 * This command emulates a bit block transfer function to move
 * display pixels from one area of the display memory to another.
 * 
 * @param[in] x0 upper left hand x coordinate or region
 * @param[in] y0 upper left hand y coordinate or region
 * @param[in] w width of region
 * @param[in] h height of region
 * @param[in] xoffset x displacement to move image
 * @param[in] yoffset y displacement to move image
 */
void dd_move_area(unsigned char x0, unsigned char y0, unsigned char w, unsigned char h, unsigned char xoffset, unsigned char yoffset);
/**
 * @brief download startup screen data to display controller
 * 
 * Upload display bitmap for startup screen
 *
 * @param[in] len the length of the bitmap (accounting for display mode)
 * @param[in] data the address of the data buffer
 */
void dd_upload_start_screen(int lon, unsigned char *data) ;
/**
 * @brief upload font data 
 *
 * This routine allows for updating the font data onboard CGRAM
 * 
 * @param len  the length of the data
 * @param data  the address of the font data buffer
 * @param sect the section of memory to update
 */  
void dd_upload_user_font(int lon, unsigned char *data, unsigned char sect) ;

/**
 * @brief draw a 256-color bitmap
 *
 * This routine will render a 256-color bitmap of the specified
 * width and height to the specified location
 *
 * @param x the x position of the upper left hand corner of the image
 * @param y the y position of the upper left hand corner of the image
 * @param w the width of the image
 * @param h the height of the image
 * @param bitmap the address of the bitmap data in memory, each byte is a pixel
 * 
 * This routine handles 1-byte per pixel (256 color indexed palette) format bitmaps.
 * <p>
 * There are online conversion utilities available <A Href="http://www.digole.com/tools/PicturetoC_Hex_converter.php">here to convert the data</a>.
 *<p>
 */
void dd_draw_bitmap256(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char *bitmap) ;

/**
 * @brief draw a 262K-color bitmap
 *
 * This routine will render a 262K-color bitmap of the specified
 * width and height to the specified location
 *
 * @param x the x position of the upper left hand corner of the image
 * @param y the y position of the upper left hand corner of the image
 * @param w the width of the image
 * @param h the height of the image
 * @param bitmap the address of the bitmap data in memory, every 3 bytes represents on pixel value
 * 
 * This routine handles 3-byte per pixel format bitmaps.
 * <p>
 * There are online conversion utilities available <A Href="http://www.digole.com/tools/PicturetoC_Hex_converter.php">here to convert the data</a>.
 *<p>
 */
void dd_draw_bitmap262K(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char *bitmap) ;
/**
 * @brief set the drawing color in 24-bit mode
 * 
 * This routine sets the current drawing color in 24bpp mode
 *
 * @param r the red component of the color (0-255)
 * @param g the green component of the color (0-255)
 * @param b the blue component of the color (0-255)
 */
void dd_set_truecolor(unsigned char r, unsigned char g, unsigned char b) ;
/**
 * @brief reset the drawing window to full screen
 * 
 * This routine will reset the drawing window to full screen mode.
 */
void dd_reset_draw_win(void);
/**
 * @brief clear drawing window
 * 
 * This routine will clear the defined drawing window.
 */
void dd_clean_win(void);
/**
 * @brief define drawing window
 * 
 * To facilitate drawing to separate regions of the display, this routine
 * lets you define the active drawing window of the display. All coordinate
 * accesses are bound to this region once it is defined.
 * 
 * @param x the x position of the upper left hand corner
 * @param y the yposition of the upper left hand corner
 * @param w the width of the window
 * @param h the height of the window
 */
void dd_define_win(unsigned char x, unsigned char y, unsigned char h, unsigned char w);



#endif /* !__DIGOLE_DISPLAY_H */
/** @}*/
