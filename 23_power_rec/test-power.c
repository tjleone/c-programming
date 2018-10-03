#include <stdio.h>
#include <stdlib.h>

unsigned power (unsigned x, unsigned y);

int main(void) {
  typedef struct param_tag {
    unsigned x;
    unsigned y;
    unsigned expected;
  } param_t;

  size_t s_params = 9;

  param_t params[] = { {.x = 0, .y = 0, .expected = 1},
		       {.x = 1, .y = -1, .expected = 1},
		       {.x = -2, .y = 0, .expected = 1},
		       {.x = -2, .y = 2, .expected = 4},
		       {.x = -2, .y = 3, .expected = -8},
		       {.x = 0, .y = -1, .expected = 0}, // answer from "correct" implementation
		       {.x = -1, .y = -1, .expected = -1}, // answer from "correct" implementation
		       {.x = 2, .y = 1, .expected = 0}, // answer from "correct" implementation
		       {.x = 2, .y = -1, .expected = 0} // answer from "correct" implementation
  };

  for (int i=0; i<s_params; i++) {
    printf("For x=%d, y=%d, expected %d, got %d\n",
	   params[i].x, params[i].y, (int)params[i].expected,
	   (int)power(params[i].x, params[i].y));
    if(power(params[i].x, params[i].y) != params[i].expected) {
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}
