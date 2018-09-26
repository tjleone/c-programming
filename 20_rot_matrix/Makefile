CC = gcc
CFLAGS = -pedantic -std=gnu99 -ggdb3 -Wall -Werror -no-pie

rotate-matrix: read-matrix.o rotate-matrix.o
	$(CC) $(CFLAGS) -o rotate-matrix read-matrix.o rotate-matrix.o

rotate-matrix.o: rotate-matrix.c
	$(CC) $(CFLAGS) -c rotate-matrix.c

.PHONY: run clean

run:
	./rotate-matrix

clean:
	rm rotate-matrix *.o *~
