/* The grader basically asks your code to read a file like this */

/* 0c 5c 8d ?1 ?2 Ac ?0 */ // see hands1.txt
/* Ks Qc Jd ?0 ?1 ?2 ?3 */

/* and then it reads specific values for the ? cards, from another file, one draw per line, for example: */

/*     Kd Kc Qs Qd */ // see draw1.txt
/*     7c Qs Qd Jh */

/*     and it makes a deck for each line in the file (draw) and asks your code to fill in the future cards, then print out the hand, sort the hand, and print the sorted hand: */

/*       Draw 0 */

/*       Hand 0: 0c 5c 8d Kc Qs Ac Kd (sorted: Ac Kc Kd Qs 0c 8d 5c ) */
/*       Hand 1: Ks Qc Jd Kd Kc Qs Qd (sorted: Kc Kd Ks Qc Qd Qs Jd ) */

/*       Draw 1 */

/*       Hand 0: Ac Qs 7c Qd 0c 8d 5c (sorted: Ac Qd Qs 0c 8d 7c 5c ) */
/*       Hand 1: Qs 7c Ks Qc Jh Qd Jd (sorted: Ks Qc Qd Qs Jd Jh 7c ) */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "cards.h"
#include "deck.h"
#include "future.h"
#include "input.h"

void test_read_input(FILE * hands_f, FILE * draws_f) {
  deck_t ** decks = read_input(hands_f, NULL, NULL);
  if(decks == NULL) {
    return;
  }
}

int main(int argc, char ** argv) {
  if(argc != 3) {
    fprintf(stderr, "Usage: %s <hand file name> <draw file name>\n", argv[0]);
    return EXIT_FAILURE;
  }
  FILE * hands_f = fopen(argv[1],"r");
  if (hands_f == NULL) {
    perror("Failed to open the input file");
    fprintf(stderr, "Did you mean to call it %s?\n", argv[1]);
    return EXIT_FAILURE;
  }
  FILE * draws_f = fopen(argv[2],"r");
  if (draws_f == NULL) {
    perror("Failed to open the input file");
    fprintf(stderr, "Did you mean to call it %s?\n", argv[2]);
    return EXIT_FAILURE;
  }

  test_read_input(hands_f, draws_f);
}
