###################################################
# filename: Makefile
# purpose:  specify rules to build myalloc 
# author:   Rowan parker
###################################################

CFLAGS = -g -Wall -O0 -std=c99

mymalloc : mymalloc.c
	gcc $(CFLAGS) -o mymalloc mymalloc.c -lm

clean : 
	rm -f mymalloc
	rm -f *.o