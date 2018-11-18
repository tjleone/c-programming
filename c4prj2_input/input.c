#include <assert.h>
#include <string.h>
#include "input.h"
#include "util.h"

/* This function reads the input from f.  Recall that the input */
/* file has one hand per line (and that we represent a hand */
/* with a deck_t).  You should allocate a deck_t for each hand */
/* and place it into an array of pointers to deck_ts, which is your */
/* answer. */
/* This function needs to tell its caller how many hands it read. */
/* We could return a struct, but we are going to do this a */
/* different way: it will fill in *n_hands with the number */
/* of hands.  This is a bit different, but you have seen it */
/* before: this is how getline "returns" the string it */
/* read and the size of the space allocated to that string. */

/* As you read the input, if you encounter future cards */
/* (?0, ?1, ...), you should use add_empty_card to */
/* create a placeholder in the hand, and then add_future_card */
/* to make sure you will update it correctly when you draw */
/* later.  Also remember that you wrote add_card_to */
/* earlier in this course, as well as card_from_letters */
/* in Course 2.  These will both be handy here! */
deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
  deck_t ** answer = NULL;
  char * line = NULL;
  size_t sz = 0;
  size_t n_decks = 0;
  if (f == NULL) {
    fprintf(stderr, "NULL pointer for input\n");
    return NULL;
  }
  while (getline(&line, &sz, f) > 0) {
    n_decks++;
    answer = realloc(answer, n_decks * sizeof(*answer));
    answer[n_decks-1] = hand_from_string(line, fc);
  }
  *n_hands = n_decks;
  return answer;
}

// recommended in README for input.c
deck_t * hand_from_string(const char * str, future_cards_t * fc) {
  deck_t * deck = make_empty_deck();
  char * hand_str = strdup(str); // can't call strtok on a const char *
  const char delim[] = " \n";
  char * token = strtok(hand_str, delim);

  while (token != NULL) {
    printf("Card string: %s\n", token);
    assert(strlen(token) == 2);
    if (token[0] == '?') {
      // add empty card deck
      card_t * cptr = add_empty_card(deck);
      // add a pointer to the empty card to fc
      size_t index = token[1] - '0';
      add_future_card(fc, index, cptr);
    } else {
      add_card_from_string_to(deck, token);
    }
    token = strtok(NULL, delim);
  }
  free(hand_str);
  return deck;
}
