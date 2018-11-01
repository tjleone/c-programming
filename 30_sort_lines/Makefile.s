CFLAGS=-ggdb3 -Wall -Werror -std=gnu99 -pedantic -fsanitize=address
sortLines: sortLines.c
	gcc $(CFLAGS) -o sortLines sortLines.c

clean:
	rm -f sortLines *~
