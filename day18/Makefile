
CC=g++
CFLAGS=-std=c++20 -g3 -pthread

.PHONY: clean test

all: part1 part2

part1: part1.cpp
	$(CC) $(CFLAGS) part1.cpp -o part1

part2: part2.cpp
	$(CC) $(CFLAGS) part2.cpp -o part2

test: part1 part2 part1.exp part2.exp sample.txt
	./part1 < sample.txt > part1.out
	./part2 < sample.txt > part2.out
	diff -q part1.out part1.exp
	diff -q part2.out part2.exp

clean:
	rm part1
	rm part2