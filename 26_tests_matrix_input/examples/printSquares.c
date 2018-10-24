#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
  if (argc != 4) {
    fprintf(stderr, "Usage: %s start end filename\n", argv[0]);
    return EXIT_FAILURE;
  }
  int start = atoi(argv[1]);
  int end = atoi(argv[2]);
  FILE * f = fopen(argv[3], "w");
  if (f == NULL) {
    perror("Could not open file"); // prints a message to stderr followed by errno msg
    return EXIT_FAILURE;
  }
  for (int i = start; i <= end; i++) {
    fprintf(f, "%d\n", i*i);
  }
  // ferror test with clearerr from
  // https://www.ibm.com/support/knowledgecenter/en/ssw_ibm_i_71/rtref/ferror.htm
  if (ferror(f)) {
    fprintf(stderr, "Error writing to file\n");
    clearerr(f); // resets error indicators
  }
  if (fclose(f) != 0) {
    perror("Failed to close the file");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
