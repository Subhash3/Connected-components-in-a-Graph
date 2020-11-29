CC=g++
CFLAGS=-Wall

all: Graph.o bcc.cpp
	$(CC) $(CFLAGS) $^ -o bcc

Graph.o: Graph.cpp Graph.h
	$(CC) $(CFLAGS) Graph.cpp -c

clean:
	rm *.o