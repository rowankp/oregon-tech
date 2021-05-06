OBJS = list.o \
       listtest.o \

CFLAGS = -Wall -g -O1
CC = gcc

all: listtest
clean:
	rm -f *.o
	rm -f listtest

list.o: Makefile list.c list.h
listtest.o: Makefile listtest.c list.h
listtest: $(OBJS)
	gcc $(OBJS) -o listtest

