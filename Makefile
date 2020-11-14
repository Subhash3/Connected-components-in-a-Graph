CC=g++
CFLAGS=-Wall

all:
	$(CC) $(CFLAGS) src/Graph.cpp -o bin/Graph

# clean:
# 	rm *.o