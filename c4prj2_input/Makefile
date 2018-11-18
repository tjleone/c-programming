CFLAGS=-ggdb3 -Wall -Werror -pedantic -std=gnu99 -Wwrite-strings

MY_OBJS=cards.o deck.o eval.o future.o input.o util.o test.o

test: $(MY_OBJS)
	gcc -o test -no-pie -ggdb3 $(MY_OBJS) $(GIVEN_OBJS)

.PHONY: run clean

run:
	./test

clean:
	rm test cards.o deck.o eval.o future.o input.o util.o test.o *~
