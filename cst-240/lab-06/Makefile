COPTS = -g -O0 -Wall -std=c99 -lreadline

all: test

client: client.c
	gcc $(COPTS) client.c -o client

server: server.c
	gcc $(COPTS) server.c -o server

clean:
	rm -f client
	rm -f server
	rm -f test_client
	rm -f test_server
	rm -f *.o
	rm -f *~

build: client server

test: build
