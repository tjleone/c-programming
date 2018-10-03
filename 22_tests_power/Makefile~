CC = gcc
CFLAGS = -pedantic -std=gnu99 -ggdb3 -Wall -Werror

test: test-subseq.o maxSeq.o
	$(CC) $(CFLAGS) -o test test-subseq.o maxSeq.o

test-subseq.o: test-subseq.c
	$(CC) $(CFLAGS) -c test-subseq.c

maxSeq.o: maxSeq.c
	$(CC) $(CFLAGS) -c maxSeq.c

.PHONY: run clean

run:
	./test

clean:
	rm test *.o *~
