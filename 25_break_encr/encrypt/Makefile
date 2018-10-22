CC = gcc
CFLAGS = -pedantic -std=gnu99 -ggdb3 -Wall -Werror -Wwrite-strings

encrypt: encrypt.o
	$(CC) $(CFLAGS) -o encrypt encrypt.o

encrypt.o: encrypt.c
	$(CC) $(CFLAGS) -c encrypt.c

.PHONY: run clean

run:
	./encrypt

clean:
	rm encrypt *.o *~
