CC = gcc
CFLAGS = -pedantic -std=gnu99 -ggdb3 -Wall -Werror -Wwrite-strings

breaker: breaker.o
	$(CC) $(CFLAGS) -o breaker breaker.o

breaker.o: breaker.c
	$(CC) $(CFLAGS) -c breaker.c

.PHONY: run clean

run:
	./breaker

clean:
	rm breaker *.o *~
