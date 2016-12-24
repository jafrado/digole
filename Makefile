#
# Digole Display Driver makefile
#
CFLAGS = -g -DDEBUG
CC=gcc

all: oledtest

oledtest: serial.c io.c digole.c main.c amg_img.c black_cat_img.c img_262k.c img_256.c img_compass.c
	$(CC) $(CFLAGS) serial.c digole.c amg_img.c black_cat_img.c img_262k.c io.c img_256.c img_compass.c main.c  -o oledtest

etags TAGS ETAGS tags:
	etags -a *.c *.h

docs:
	doxygen Doxyfile

clean: 
	rm -f *.o rm ./oledtest tags ETAGS TAGS
	rm -fr doc/html doc/latex



