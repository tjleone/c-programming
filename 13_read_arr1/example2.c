#include <stdio.h>
#include <stdlib.h>

int sumArray(int * array, int n) {
  int answer = 0;
  for (int i = 0; i < n; i++) {
    answer += array[i];
  }
  return answer;
}

int main(void) {
  int data[4] = {4, 6, 8, 3};
  int sum = sumArray(data, 4);
  printf("%d\n", sum);
  return EXIT_SUCCESS;
}
