#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

int main(void) {
  typedef struct param_tag {
    int * array;
    size_t n;
    size_t expected;
  } param_t;

  size_t s_params = 15;

  int arrays[15][3] = {{0}, {0}, {0,0,0}, {0,0,1}, {0,1,0}, {1,0,0},
		       {0,1,2}, {0,2,1}, {1,0,2}, {1,2,0}, {2,0,1}, {2,1,0},
		       {1,2,3}, {3,1,2}, {0,0,-1}
  };

  param_t params[] = { {.array = &arrays[0][0], .n = 0, .expected = 0},
			{.array = &arrays[1][0], .n = 1, .expected = 1},
		        {.array = &arrays[2][0], .n = 3, .expected = 1},
		        {.array = &arrays[3][0], .n = 3, .expected = 2},
		        {.array = &arrays[4][0], .n = 3, .expected = 2},
		        {.array = &arrays[5][0], .n = 3, .expected = 1},
		        {.array = &arrays[6][0], .n = 3, .expected = 3},
		        {.array = &arrays[7][0], .n = 3, .expected = 2},
		        {.array = &arrays[8][0], .n = 3, .expected = 2},
		        {.array = &arrays[9][0], .n = 3, .expected = 2},
		        {.array = &arrays[10][0], .n = 3, .expected = 2},
		        {.array = &arrays[11][0], .n = 3, .expected = 1},
		        {.array = &arrays[12][0], .n = 2, .expected = 2},
		        {.array = &arrays[13][0], .n = 2, .expected = 1},
		        {.array = &arrays[14][0], .n = 3, .expected = 1}
  };

  for (int i=0; i<s_params; i++) {
    printf("For array %d, expected %d, got %d\n",
	   i, (int)params[i].expected,
	   (int)maxSeq(params[i].array, params[i].n));
    if(maxSeq(params[i].array, params[i].n) != params[i].expected) {
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}
