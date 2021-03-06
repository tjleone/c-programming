#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * ssize_t getline(char **linep, // pointer to malloced buffer where line will be written or NULL 
 *                 size_t *linecapp, // pointer to size of malloced buffer
 *                 FILE *stream); // pointer to file to be read
 *
 * Returns the length of the string read or -1. Length of string includes '\n' at end of line but
 * but not '\0'. In other words, it returns the string length that would be given by strlen()
 */
int main(void) {
  size_t sz = 0;
  ssize_t len = 0;
  char * line = NULL;
  FILE * f = fopen("names.txt", "r");
  while ((len = getline(&line, &sz, f)) >= 0) {
    printf("%s|len=%ld|strlen(line=%ld)\n", line, len, strlen(line));
  }
  free(line);
  fclose(f);
  return EXIT_SUCCESS;
}
