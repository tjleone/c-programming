#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINE_SIZE 12

int load_matrix(FILE *fp, char matrix[][10], size_t nitems);
void rotate(char matrix[10][10]);

int main(int argc, char* argv[]) {
// 	- Your program will take one command line argument, a string
//    specifying the input file to read.
//  - If there are any errors, your program should print an
//    appropriate message to stderr, and exit with EXIT_FAILURE.
  if(argc != 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return EXIT_FAILURE;
  }
  FILE * fptr = fopen(argv[1], "r");
  if (fptr == NULL) {
    perror("Failed to open the input file!");
    return EXIT_FAILURE;
  }

  char matrix[10][10];
  if (load_matrix(fptr, matrix, 10) != 0) {
    return EXIT_FAILURE;
  }

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

  rotate(matrix);

  for(int i = 0; i < 10; i++) {
    for(int j = 0; j < 10; j++) {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }

  return EXIT_SUCCESS;
}

int load_matrix(FILE *fp, char matrix[][10], size_t nitems) {
//  - The input file should contain 10 lines, each of which
//    have 10 (non-newline) characters (plus a newline).
//  - If there are any errors, your program should print an
//    appropriate message to stderr, and exit with EXIT_FAILURE.
//  Hint:
//  - You may find the strchr useful for error checking that
//    you read a proper line (10 non-newline characters, then a newline).
  char buf[LINE_SIZE];
  int i = 0;

  // an embedded value of -1 would be a problem if we used fgetc, since
  // fgetc returns EOF (-1) on failure
  while (fgets(buf, LINE_SIZE, fp) != NULL) {
    // strchr returns a pointer to the first occurrence of the character
    // c in the string str, or NULL if the character is not found.
    if (strchr(buf, '\n') == NULL) {
      fprintf(stderr, "Line %d is too long!\n", i+1);
      buf[LINE_SIZE-1] = '\0';
      printf("First %d chars in line %d: |%s|\n", LINE_SIZE-1, i+1, buf);
      return -1;
    }
    if (i > 9) {
      fprintf(stderr, "Too many lines in the file (%d lines)!\n", i);
      return -1;
    }
    for(int j=0; j<10; j++) {
      if(buf[j] == '\n') {
	fprintf(stderr, "Line %d is too short!\n", i+1);
	buf[j] = '\0';
        printf("First %d chars in line %d: |%s|\n", j, i+1, buf);
        return -1;
      }
      matrix[i][j] = buf[j];
    }
    i++;
  }
  if (i < 10) {
    fprintf(stderr, "Only %d lines were read!\n", i);
    return -1;
  }
  return 0;
}

void rotate(char matrix[10][10]) {
//  - Your program should then rotate this 90 degrees clockwise,
//    and print the result on stdout.
//    Note that sample.txt provides sample input, and 
//    sample.out provides sample output.
  char copy[10][10];
  for (int i=0; i < 10; i++) {
    for (int j=0; j < 10; j++) {
      //      if (!isprint(matrix[i][j])) {
      //	printf("Character %x on line %d, column %d is not printable!\n", matrix[i][j], i, j);
      //      }
      copy[i][j] = matrix[i][j];
    }
  }

  for (int i=0; i < 10; i++) {
    for (int j=0; j < 10; j++) {
      matrix[i][j] = copy[9-j][i];
    }
  }
}
