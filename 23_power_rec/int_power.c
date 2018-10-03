#include <stdio.h>

int power_helper(int x, int y, int ans) {
  if (y == 0) {
    return ans;
  }
  
  printf("1:Calling power_helpwer with %d, %d, %d\n", x, y, ans);
  return power_helper(x, y-1, ans*x);
}

unsigned power(unsigned x, unsigned y) {
  if (x == 1) {
    return 1;
  }
  int base = (int)x;
  int exp = (int)y;
  printf("0:Calling power_helpwer with %d, %d, %d\n", base, exp, 1);
  return (unsigned)power_helper(base, exp, 1);
}
