CC = gcc
CFLAGS = -pedantic -std=gnu99 -ggdb3 -Wall -Werror

test: test.o
	$(CC) $(CFLAGS) -o test test.o

test.o: test.c
	$(CC) $(CFLAGS) -c test.c

.PHONY: run clean

run:
	./test

clean:
	rm test *.o *~
