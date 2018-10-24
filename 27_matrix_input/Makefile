CC = gcc
CFLAGS = -pedantic -std=gnu99 -ggdb3 -Wall -Werror -Wwrite-strings

rotateMatrix: rotateMatrix.o
	$(CC) $(CFLAGS) -o rotateMatrix rotateMatrix.o

rotateMatrix.o: rotateMatrix.c
	$(CC) $(CFLAGS) -c rotateMatrix.c

.PHONY: run clean

run:
	./rotateMatrix

clean:
	rm rotateMatrix *.o *~
