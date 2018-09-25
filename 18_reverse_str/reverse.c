#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const size_t MAX_SIZE = 100;
char * strnbcpy(char *dest, const char *src, size_t n);
void reverse(char * str);

// n is the index of the '\0' in src or MAX_SIZE
// dest must have a size of n
char * strnbcpy(char *dest, const char *src, size_t n) {
  size_t i;

  for (i = 0; i < n && src[i] != '\0'; i++)
    dest[i] = src[n-i-1];
  dest[n] = '\0';

  return dest;
}


void reverse(char * str) {
  size_t n = strnlen(str, MAX_SIZE);
  if(n == 0) {
    return;
  }

  char copy[n];
  printf("n=%ld, str=%s\n", n, str);
  strncpy(copy, str, n);
  copy[n] = '\0';
  printf("copy=%s\n",copy);
  strnbcpy(str, copy, n);    
}

int main(void) {
  char str0[] = "";
  char str1[] = "123";
  char str2[] = "abcd";
  char str3[] = "Captain's log, Stardate 42523.7";
  char str4[] = "Hello, my name is Inigo Montoya.";
  char str5[] = "You can be my wingman anyday!";
  char str6[] = "Executor Selendis! Unleash the full power of your forces! There may be no tomorrow!";
  char * array[] = {str0, str1, str2, str3, str4, str5, str6};
  for (int i = 0; i < 7; i++) {
    printf("array[%d]=%s\n",i, array[i]);
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}
