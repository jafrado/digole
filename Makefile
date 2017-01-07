#
# Digole Display Driver library and test apps makefile
#
CFLAGS = -g -DDEBUG
CC=gcc
SYS=$(shell uname -m)

# Pick serial interface for x86, SPI for PI
ifeq ($(SYS), x86_64)
SERIAL=serial.c io.c
else
SERIAL=rpi_spi.c io_spi.c
endif

all: showtarget oledtest mandel fip imgload

showtarget:
	@echo "Building for [$(SYS)]"

oledtest: $(SERIAL) digole.c main.c \
	amg_img.c black_cat_img.c img_262k.c img_256.c img_compass.c
	$(CC) $(CFLAGS) $(SERIAL) digole.c amg_img.c black_cat_img.c \
	img_262k.c  img_256.c img_compass.c main.c  -o $@

imgload: imgload.c digole.c $(SERIAL)
	$(CC) $(CFLAGS) imgload.c digole.c $(SERIAL) -o $@

mandel: digole.c $(SERIAL) mandel.c
	$(CC) $(CFLAGS) digole.c $(SERIAL) mandel.c  -o $@

fip: digole.c $(SERIAL) fip.c
	$(CC) $(CFLAGS) digole.c $(SERIAL) fip.c -o $@ -lm

etags TAGS ETAGS tags:
	etags -a *.c *.h

docs:
	doxygen Doxyfile

clean: 
	rm -f *.o rm ./oledtest ./mandel ./fip ./imgload tags ETAGS TAGS
	rm -fr doc/html doc/latex



