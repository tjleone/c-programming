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
#include "eval.h"
#include "future.h"
#include "input.h"

void print_hands(deck_t ** decks, size_t n_hands, FILE * fout);

void free_memory(future_cards_t * fc, deck_t ** decks, int n_hands) {

  // Now free up the hands, which will free up the cards
  // pointers
  for (int i = 0; i < n_hands; i++) {
    //    printf("Calling free_deck for deck %d\n", i);
    free_deck(decks[i]);
    //    printf("...back from free_future_cards\n");
  }
  free(decks);
  for(int i=0; i < fc->n_decks; i++) {
    free(fc->decks[i].cards);
  }
  free(fc->decks);
}

void test_read_input(FILE * hands_f, FILE * draws_f) {
  /* The grader basically asks your code to read a file like this */

  /* 0c 5c 8d ?1 ?2 Ac ?0 */ // see hands1.txt
  /* Ks Qc Jd ?0 ?1 ?2 ?3 */
  future_cards_t unknown;
  unknown.n_decks = 0;
  unknown.decks = NULL;
  future_cards_t * fc = &unknown;
  size_t n_hands = 0;
  deck_t ** decks = read_input(hands_f, &n_hands, fc);
  if(decks == NULL) {
    return;
  }

  /* and then it reads specific values for the ? cards, from another file, one draw per line, for example: */
  int draw = 0;
  char * line = NULL;
  size_t sz = 0;

  while(getline(&line, &sz, draws_f) != EOF) {
    /*       Draw 0 */
    printf("Draw %d\n", draw);
    printf("%s", line);
    deck_t * deckptr = hand_from_string(line, NULL);
    future_cards_from_deck(deckptr, fc);
    print_hands(decks, n_hands, stdout);
    free_deck(deckptr);
    draw++;
  }
  free(line);

/*       Hand 0: 0c 5c 8d Kc Qs Ac Kd (sorted: Ac Kc Kd Qs 0c 8d 5c ) */
/*       Hand 1: Ks Qc Jd Kd Kc Qs Qd (sorted: Kc Kd Ks Qc Qd Qs Jd ) */
  free_memory(fc, decks, n_hands);
}

void print_hands(deck_t ** decks, size_t n_hands, FILE * fout) {
  for(int i=0; i < n_hands; i++) {
    sort_hand(decks[i]);
    fprint_hand(fout, decks[i]);
    fprintf(fout,"\n");
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
