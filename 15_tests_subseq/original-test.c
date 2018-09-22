#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

int main(void) {
  int empty[0];
  int one[1] = {0};
  int three[3] = {0};
  if (maxSeq(empty, 0) != 0) {
    return EXIT_FAILURE;
  }
  if (maxSeq(three, 3) != 0) {
      return EXIT_FAILURE;
  }
  if (maxSeq(one, 1) !=0) {
    return EXIT_FAILURE;
  }
  
  three[2] = 1;
  if (maxSeq(three, 3) != 2) {
      return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
