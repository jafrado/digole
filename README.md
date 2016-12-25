# Overview

This library implements Text and Graphics functionality for the Digole Serial OLED Display modules made by Digole . Tested and verified with [Digole 1.8" Serial: UART/I2C/SPI OLED True Color 160x128  OLED Module DS160128COLED-46](http://www.digole.com/index.php?productID=859)

# HW Setup
For testing and initial bringup, the core library runs on Linux via USB Serial and only 3 wires (TXD, VCC, GND) are soldered to the module. Pinout is defined as below:

    Black - Ground (connect to ground on OLED module)
    Brown - CTS
    Red - VCC (3V model used - connect to VCC on OLED module)
    Orange - TXD (connect to Data on OLED module)
    Yellow - RXD (not currently used - may be in the future)
    Green - RTS

For more information on the FTDI USB->Serial Adapter Cable, see also: http://www.ftdichip.com/Support/Documents/DataSheets/Cables/DS_TTL-232R_CABLES.pdf

# Module Connections
The Digole HW module is setup as below. Pin-out for the module is from the Digole HW Adapter manual:
![HW Setup Diagram](http://realflightsystems.com/techpubs/digole/hw_setup_ttl2323v3.jpg)

# API Documentation
Doxygen is used for [API Documentation](http://realflightsystems.com/techpubs/digole/html/index.html)

# Porting
Relevant porting files and API's are defined in io.c and serial.c for the Linux platform

# Testing
A test application (oledtest) is provided to verify the functionality and perform testing.
Some snapshots are shown below.
![Black cat image](http://realflightsystems.com/techpubs/digole/black-cat-128x128_rendered.jpg)
![Bahamas image](http://realflightsystems.com/techpubs/digole/bahamas3_160x108_rendered.jpg)
![Rendered text](http://realflightsystems.com/techpubs/digole/text_rendered.jpg)
![Blackrock Truecolor Image](http://realflightsystems.com/techpubs/digole/Aidain_Sojourner_ID2015_BR_4thofJuplaya_160x120_rendered.JPG)

A [mandelbrot fractal generator](http://www.physics.emory.edu/faculty/weeks//software/mand.html) program which outputs PNG has been modified to use the display library.
 ![Mandelbrot image](http://realflightsystems.com/techpubs/digole/mandelbrot.jpg)

Additional utilities and test applications may be provided in the future.

# Reference

See also: http://www.digole.com/index.php?productID=859

See also: http://www.digole.com//images/file/Tech_Data/Digole_Serial_Display_Adapter-Manual.pdf

## Software

The software is written in C99, Linux kernel coding style and is distributed under the MIT License.
Doxygen is used for[http://realflightsystems.com/techpubs/digole/html/](API Documentation)


## Copyright
    Copyright (C) 2016 Real Flight Systems 

## Author
    James F Dougherty <jfd@realflightsystems.com> 
