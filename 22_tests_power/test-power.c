#include <stdio.h>
#include <stdlib.h>

unsigned power (unsigned x, unsigned y);

int main(void) {
  typedef struct param_tag {
    unsigned x;
    unsigned y;
    unsigned expected;
  } param_t;

  size_t s_params = 15;

  param_t params[] = { {.x = 0, .y = 0, .expected = 1},
		       {.x = 1, .y = -1, .expected = 1},
		       {.x = -2, .y = 0, .expected = 1},
		       {.x = -2, .y = 2, .expected = 4},
		       {.x = -2, .y = 3, .expected = -8},
		       {.x = 0, .y = -1, .expected = 1}, // don't know what to expect
		       {.x = -1, .y = -1} // don't know what to expect
  };

  for (int i=0; i<s_params; i++) {
    printf("For x=%d, y=%d, expected %d, got %d\n",
	   i, (int)params[i].expected,
	   (int)power(params[i].x, params[i].y));
    if(power(params[i].x, params[i].y) != params[i].expected) {
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}
