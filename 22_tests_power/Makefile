CC = gcc
CFLAGS = -pedantic -std=gnu99 -ggdb3 -Wall -Werror

test: test-power.o power.o
	$(CC) $(CFLAGS) -o test test-power.o power.o

test-power.o: test-power.c
	$(CC) $(CFLAGS) -c test-power.c

power.o: power.c
	$(CC) $(CFLAGS) -c power.c

.PHONY: run clean

run:
	./test

clean:
	rm test *.o *~
