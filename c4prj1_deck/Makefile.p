CFLAGS=-ggdb3 -Wall -Werror -pedantic -std=gnu99 -no-pie
GIVEN_OBJS=deck-c4.o  eval-c4.o  future.o  input.o  main.o
MY_OBJS=cards.o deck.o eval.o

test-deck: deck.o test-deck.o deck-c4.o cards.o
	gcc -o test-deck -no-pie -ggdb3 deck.o test-deck.o deck-c4.o cards.o
clean:
	rm test poker cards.o my-test-main.o *~
