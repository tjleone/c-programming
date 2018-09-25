#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char * str) {
  if(*str == '\0') {
    return;
  }
  int n = 0;
  while (str[n] != 0) {
    n++;
  }
  char copy[n];
  char *p = strncpy(copy, str, n);
  copy[n] = '\0';
  p = &copy[n-1];

  for(char *q = str; p >= copy; p--, q++) {
    *q = *p;
  }

    
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
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}
