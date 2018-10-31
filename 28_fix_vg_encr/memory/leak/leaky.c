#include <stdio.h>
#include <stdlib.h>

// compile with -fsanitize=address or -fsanitize=leak for analysis with LeakSanitizer
// Shouldn't compile with LeakSanitizer except when developing/debugging
// Possible memory errors:
//   - not freeing up memory allocated by malloc
//   - double freeing
//   - trying to free in the middle of the allocated block
//   - trying to free memory that's not in the heap (e.g. memory in the stack)
// Note that calling free on a NULL pointer does nothing.
// When you call realloc, your block may be moved. If so, contents from the original
// block will be copied over. realloc returns a void * to the location of the
// reallocated block. Think of realloc as malloc + copy + free(old block)
// You can use realloc to increase or reduce the size of a block.
// Always assume that the block will be move (even though sometimes it won't be)

int doSomeComputation(int x, int nitems, int * p) {
  for (int i; i < nitems; i++) {
    p[i] = i;
    x += i;
  }
  return x;
}

int main(void) {
  int x = 0;
  for (int i = 10; i < 100; i++) {
    int * p = malloc(i * sizeof(*p));
    x = doSomeComputation(x, i, p);
    free(p); // without this free statement, we have a serious leak
  }
  printf("Answer %d\n", x);
  return EXIT_SUCCESS;
}
