#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// test with the following:
//     $ ./console_input < input.txt

/*
 * ssize_t getline(char **linep, // pointer to malloced buffer where line will be written or NULL 
 *                 size_t *linecapp, // pointer to size of malloced buffer
 *                 FILE *stream); // pointer to file to be read
 *
 * Returns the length of the string read or -1. Length of string includes '\n' at end of line but
 * but not '\0'. In other words, it returns the string length that would be given by strlen()
 */

// test case to check: What if programmer forgot to set curr = NULL in while loop?
// Debugging is easier if you use valgrind throughout the testing and debugging process
// Do *NOT* compile with -fsanitize=address when using valgrind

int str_comparator(const void* p1, const void* p2) {
  const char * const *str1 = p1;
  const char * const *str2 = p2;
  return strcmp(*str1, *str2);
}

int main(void) {
  char **lines = NULL;
  char *curr = NULL;
  size_t sz;
  ssize_t i = 0;
  while (getline(&curr, &sz, stdin) >= 0) {
    lines = realloc(lines, (i+1) * sizeof(*lines));
    lines[i] = curr;
    curr = NULL; // make sure we get a new block from next realloc
    i++;
  }
  free(curr);
  qsort(lines, i, sizeof(*lines), str_comparator);
  for (size_t j = 0; j < i; j++) {
    printf("%s", lines[j]);
    free(lines[j]);
  }
  free(lines);
  return EXIT_SUCCESS;
}
