CC=gcc
AR=ar
CFLAGS=-Wall
all: freq

freq: frequency.c
	$(CC) $(CFLAGS) frequency.c -o frequency

.PHONY: clean all

clean:
	rm -f *.o *.a *.so freq