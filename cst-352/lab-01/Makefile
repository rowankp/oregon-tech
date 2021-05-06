###################################################
# filename: Makefile
# purpose:  specify rules to build filter programs 
# author:   Rowan parker
###################################################

CFLAGS = -g -Wall -O0 -std=c99

all : prefilter postfilter process

prefilter : prefilter.c 
	gcc $(CFLAGS) prefilter.c -o prefilter

postfilter : postfilter.c 
	gcc $(CFLAGS) postfilter.c -o postfilter

process : process.c
	gcc $(CFLAGS) process.c -o process

clean : 
	rm -f prefilter 
	rm -f postfilter
	rm -f process
	rm -f *.o