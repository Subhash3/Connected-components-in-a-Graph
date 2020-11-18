CC=g++
CFLAGS=-Wall

all: Graph.o main.cpp
	$(CC) $(CFLAGS) $^ -o main

Graph.o: Graph.cpp
	$(CC) $(CFLAGS) $^ -c

clean:
	rm *.o