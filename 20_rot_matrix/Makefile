CC = gcc
CFLAGS = -pedantic -std=gnu99 -ggdb3 -Wall -Werror -no-pie

rotate-matrix: read-matrix.o rotate.o
	$(CC) $(CFLAGS) -o rotate-matrix read-matrix.o rotate.o

rotate.o: rotate.c
	$(CC) $(CFLAGS) -c rotate.c

.PHONY: run clean

run:
	./rotate-matrix

clean:
	rm rotate-matrix rotate.o *~
