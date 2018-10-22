#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INDEX_OF_E 4

int break_it(FILE* fptr);
int index_of_max(int values[], int nvalues);
int max_to_key(int max);

int main(int argc, char* argv[]) {
  if(argc != 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return EXIT_FAILURE;
  }
  FILE * fptr = fopen(argv[1], "r");
  if (fptr == NULL) {
    perror("Failed to open the input file!");
    return EXIT_FAILURE;
  }

  int key = break_it(fptr);

  if(!feof(fptr)) {
    fprintf(stderr, "Didn't reach end of file\n");
    return EXIT_FAILURE;
  } else if(ferror(fptr)) {
    fprintf(stderr, "Error reading input\n");
    return EXIT_FAILURE;
  }
  if (fclose(fptr) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }

  printf("%d\n", key);
  return EXIT_SUCCESS;
}

int index_of_max(int values[], int nvalues) {
  int index_of_max = 0;
  int max = 0;
  for(int i=0; i<nvalues; i++) {
    if (values[i] > max) {
      max = values[i];
      index_of_max = i;
    }
  }
  return index_of_max;
}

int max_to_key(int max) {
  int key = max - INDEX_OF_E;
  if (key < 0) {
    key += 26;
  }
  return key;
}

int break_it(FILE* fptr) {
  int c;
  int frequencies[26] = {0};
  while ( (c=fgetc(fptr)) != EOF ) {
    if (isalpha(c)) {
      c = tolower(c);
      c -= 'a';
      frequencies[c] += 1;
    }
  }
  int max = index_of_max(frequencies, 26);
  return max_to_key(max);
}
