CFLAGS=-I/usr/include/tcl8.6 -D_GNU_SOURCE
LDFLAGS=-L/usr/lib -ltcl8.6 -lm -lraylib

all: raylib.c
	gcc -fPIC $(CFLAGS) -c raylib.c -o raylib.o
	gcc -shared raylib.o $(LDFLAGS) -o raylib.so