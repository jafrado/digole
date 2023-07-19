/** 
 * @file serial.h
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
int serial_open(char* comport, int highspeed);

/**
 * @brief serial port close
 * 
 * Close the serial port file descriptor and restore terminal and HW
 * com port to their original settings.
 *
 * @param sfd serial file descriptor returned from #serial_open
 */
void serial_close(int sfd);

/** @}*/
