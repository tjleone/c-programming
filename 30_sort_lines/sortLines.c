#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

char ** sortFile(FILE * f, size_t * nitems) {
  char * line = NULL;
  size_t sz = 0;
  char ** array = NULL;
  size_t n = 0;
  while (getline(&line, &sz, f) >= 0) {
    n++;
    array=realloc(array, n * sizeof(*array));
    array[n-1] = line; // should work because of next line
    line = NULL; // make sure a new block is allocated
  }
  free(line);
  sortData(array, n);
  
  *nitems = n;
  return array;
}

void printSortedFile(FILE * f) {
  size_t n = 0;
  char ** array = sortFile(f, &n);
  for (int i=0; i < n; i++) {
    printf("%s", array[i]);
    free(array[i]);
  }
  free(array);
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    printSortedFile(stdin);
  } else if (argc > 1) {
    for (int i=1; i < argc; i++) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
	perror("Could not open file");
	return EXIT_FAILURE;
      }
      printSortedFile(f);
      fclose(f);
    }
  }
  return EXIT_SUCCESS;
}
