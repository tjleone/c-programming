
unsigned power_helper(unsigned x, unsigned y, unsigned ans) {
  if (y == 0) {
    return ans;
  }
  
  return power_helper(x, y-1, ans*x);
}

unsigned power(unsigned x, unsigned y) {
  if (x == 1) {
    return x;
  } else if (x == 0) {
    if (y == 0) {
      return 1;
    } else {
      return 0;
    }
  } else if ((int)y < 0) {
    return 0;
  }
  return power_helper(x, y, 1);
}
