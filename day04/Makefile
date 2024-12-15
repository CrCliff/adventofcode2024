
CC=g++
CFLAGS=-std=c++20

.PHONY: clean test

all: part1 part2

part1: part1.cpp lib.hpp lib.cpp
	$(CC) $(CFLAGS) lib.cpp part1.cpp -o part1

part2: part2.cpp lib.hpp lib.cpp
	$(CC) $(CFLAGS) lib.cpp part2.cpp -o part2

test: part1 part2 part1.exp part2.exp sample1.txt sample2.txt
	./part1 < sample1.txt > part1.out
	./part2 < sample2.txt > part2.out
	# TODO: Part 1 vs 2 requires hard-coded changes...
	# diff -q part1.out part1.exp
	diff -q part2.out part2.exp

clean:
	rm part1
	rm part2