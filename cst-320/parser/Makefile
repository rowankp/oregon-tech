###########################################################
# filename: Makefile 
# purpose: Makefile for CST320 Lab 3. 
# author: Rowan Parker (rowan.parker@oit.edu)
# date: 01/23/20

COPTS = -Wall -g -c  -O0 -std=c++11
OBJS = main.o \
       utils.o \
       parser.o \
       scanner.o \

all: parser

clean:
	rm -f $(OBJS)
	rm -f parser
	rm -f out*
	rm -f *.c
	rm -f *.o

.c.o:
	g++ $(COPTS) $? -o $@

.cpp.o:
	g++ $(COPTS) $? -o $@

main.o: main.cpp scanner.o parser.o
	g++ $(COPTS) main.cpp -o main.o

utils.o: utils.h utils.cpp
	g++ $(COPTS) utils.cpp -o utils.o

scannerlex.c: scanner.l
	flex -o scannerlex.c scanner.l

scanner.o: scannerlex.c
	g++ $(COPTS) -Wno-sign-compare $? -o $@

parser.o: parse.h parse.cpp utils.o
	g++ $(COPTS) parse.cpp -o parser.o

parser: $(OBJS)
	g++ $(OBJS) -o parser
