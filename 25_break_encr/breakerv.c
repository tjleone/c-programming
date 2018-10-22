/* RETURN VALUE FOR fgets
 * On success, the function returns str.
 * If the end-of-file is encountered while attempting 
 * to read a character, the eof indicator is set (feof). 
 * If this happens before any characters could be read, 
 * the pointer returned is a null pointer (and the 
 * contents of str remain unchanged).
 * If a read error occurs, the error indicator (ferror) 
 * is set and a null pointer is also returned (but the 
 * contents pointed by str may have changed).
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINE_SIZE 5

int break_it(FILE* fptr);
int index_of_max(int values[], int nvalues);
void test_index_of_max();
void test(void(*test_f)(const void *expected, const void*got), void* expected, void* got);

int compare_ints(const void *arg1, const void *arg2)
{
  return *(int*)arg1 - *(int*)arg2;
}

int compare_strings(const void *arg1, const void *arg2)
{
  return(strcmp(*(char **)arg1, *(char **)arg2));
}

void test_ints(const void *arg1, const void *arg2) {
  int expected = *(int*)arg1;
  int got = *(int*)arg2;
  char prefix[3] = "OK";
  if (expected != got) {
    prefix[0] = ' '; prefix[1] = 'X';
  }
  printf("%s: expected %d, got %d\n", prefix, expected, got);
}

void test_index_of_max() {
  int test1[] = {0,1,2,3,4};
  int test2[] = {4,3,2,1,0};
  int test3[] = {0, 0, 4, 0, 0};
  int test4[] = {4, 4, 4, 4, 4};
  int test5[] = {3, 1, 0, 4, 2};
  int test6[] = {3, 1, 0, 4, 2};

  int * tests[6] = {test1, test2, test3, test4, test5, test6};

  int four = 4;
  //int zero = 0;
  for (int i=0; i<6; i++) {
    int igot = index_of_max(tests[i],5);
    int got = tests[i][igot];
    test(test_ints, &four, &got);
  }
}

void test(void(*test_f)(const void *expected, const void*got), void* expected, void* got) {
  test_f(expected, got);
}

int main(int argc, char* argv[]) {
  if(argc != 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return EXIT_FAILURE;
  }
  FILE * fptr = fopen(argv[1], "r");
  if (fptr == NULL) {
    perror("Failed to open the input file!");
    return EXIT_FAILURE;
  }

  //  test_index_of_max();
  
  int key = break_it(fptr);
  /*
   * fread() does not distinguish between end-of-file and error.
   * So when fgets comes back with NULL, we don't know which of 
   * these happened--end-of-file or error?
   * Callers must use feof(3) and ferror(3) to determine which occurred.
   */

  if(feof(fptr)) {
    ;
    //printf("End of file was reached\n");
  } else if(ferror(fptr)) {
    printf("Error reading input\n");
    return EXIT_FAILURE;
  } else {
    printf("Didn't read entire input file\n");
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
  //  printf("nvalues=%d\n", nvalues);
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

int break_it(FILE* fptr) {
  int c; // for test cases, consider that if c is declared char, EOF won't be read correctly!
  // idea for test: write all chars, 0-255 to file, then some more characters, line "\nThis is the last line\n"
  // and make sure the last line is read from the file
  // This would fail if char c was used to read from the file instead of int c, because EOF would
  // be forced to be one of the chars 0-255
  int frequencies[26] = {0};
  while ( (c=fgetc(fptr)) != EOF ) {
    if (isalpha(c)) {
      c = tolower(c);
      c -= 'a';
      frequencies[c] += 1;
    }
  }
  int imost_freq = index_of_max(frequencies, 26);
  //  printf("Most frequent char is %c\n", 'a' + imost_freq);
  return imost_freq;
}

void read_with_fgets(FILE* fp) {
  char buf[LINE_SIZE];
  int i = 0;

  while (fgets(buf, sizeof(buf), fp) != NULL) {
    // strchr returns a pointer to the first occurrence of the character
    // c in the string str, or NULL if the character is not found.
    if (strchr(buf, '\n') == NULL) {
      printf("Line %d is too long!\n", i+1);
      buf[LINE_SIZE-1] = '\0';
      printf("First %d chars in line %d: |%s|\n", LINE_SIZE-1, i+1, buf);
      return;
    }
    printf ("Line %4d: %s\n", i, buf);
    i++;
  }
}
