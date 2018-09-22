#include <stdio.h>
#include <stdlib.h>

int max(int x, int y) {
  if (x > y) {
    return x;
  } else {
    return y;
  }
}

size_t maxSeq(int * array, size_t n) {
  if (n <= 0) {
    return 0;
  }
  if (n == 1) {
    return 1;
  }
  int maxLen = 1;
  int currLen = 1;
  for (int i = 1; i < n; i++) {
    if (array[i] > array[i-1]) {
      currLen++;
    } else {
      if (currLen > maxLen) {
	maxLen = currLen;
      }
      currLen = 1;
    }
  }
  return max(maxLen, currLen);
}
