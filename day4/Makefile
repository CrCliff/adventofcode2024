
CC=g++
CFLAGS=-std=c++20

.PHONY: clean

all: part1 part2

part1: part1.cpp lib.hpp lib.cpp
	$(CC) $(CFLAGS) lib.cpp part1.cpp -o part1

part2: part2.cpp lib.hpp lib.cpp
	$(CC) $(CFLAGS) lib.cpp part2.cpp -o part2

clean:
	rm part1
	rm part2