CC = gcc
CFLAGS = -pedantic -std=gnu99 -ggdb3 -Wall -Werror -Wwrite-strings

printSquares: printSquares.o
	$(CC) $(CFLAGS) -o printSquares printSquares.o

printSquares.o: printSquares.c
	$(CC) $(CFLAGS) -c printSquares.c

.PHONY: run clean

run:
	./printSquares

clean:
	rm printSquares *.o *~
