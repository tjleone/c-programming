CCFLAGS=-Wall -pedantic -std=gnu99 -Werror -ggdb3 -fsanitize=address
minesweeper: minesweeper.c
	gcc  -o minesweeper $(CCFLAGS) minesweeper.c
