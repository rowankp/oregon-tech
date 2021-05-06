###########################################################
# Filename: Makefile
# Purpose: Makefile for CST320 labs 1, 2, 2b, and 4
# Author: Rowan Parker (rowan.parker@oit.edu)
# Date: 01/21/20

COPTS = -Wall -g -c  -O0 -std=c++11
OBJS = main.o \
       pascallex.o \
       pascalparse.o\
       cVisitor.o

all: pascal

clean:
	rm -f $(OBJS)
	rm -f pascallex.c
	rm -f pascalparse.c
	rm -f pascalpasre.h
	rm -f pascal
	rm -f out*

.c.o:
	g++ $(COPTS) $? -o $@

.cpp.o:
	g++ $(COPTS) $? -o $@

main.o: main.cpp pascalparse.c  pascallex.c 
	g++ $(COPTS) main.cpp -o $@

pascallex.o: pascallex.c
	g++ $(COPTS) -Wno-sign-compare $? -o $@

pascallex.c: pascal.l pascalparse.c
	flex -o pascallex.c pascal.l

pascalparse.c: pascal.y
	bison --defines=pascalparse.h pascal.y -o pascalparse.c

pascal: $(OBJS)
	g++ $(OBJS) -o pascal

