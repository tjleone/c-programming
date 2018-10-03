CC = gcc
CFLAGS = -pedantic -std=gnu99 -ggdb3 -Wall -Werror

test-power: test-power.o power.o
	$(CC) $(CFLAGS) -o test-power test-power.o power.o

test-power.o: test-power.c
	$(CC) $(CFLAGS) -c test-power.c

power.o: power.c
	$(CC) $(CFLAGS) -c power.c

.PHONY: run clean

run:
	./test-power

clean:
	rm test-power *.o *~
