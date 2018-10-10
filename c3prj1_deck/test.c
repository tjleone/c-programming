#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "cards.h"
#include "deck.h"

deck_t make_hand(size_t n_cards) {
  assert(n_cards > 0 && n_cards <= 52);
  // review the stuff on multidimensional arrays
  // Notice that you are given functions
  // see "The below functions will be done in course 4"
  /*
   * deck_t * make_deck_exclude(deck_t * excluded_cards);
   * void add_card_to(deck_t * deck, card_t c);
   * card_t * add_empty_card(deck_t * deck);
   * void free_deck(deck_t * deck) ;
   * deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) ;
   *
   * You will need to add deck-c4.o to Makefile
  */
  deck_t temp;
  temp.cards = NULL;
  temp.n_cards = 0;
  int cardNo = 0;
  for(int i=0; i<n_cards && cardNo < 52; i++, cardNo+=52/n_cards) {
    printf("adding card number %d with value %d\n", i, cardNo);
    add_card_to(&temp, card_from_num(cardNo));
  }
  printf("temp.n_cards=%ld, n_cards=%ld\n", temp.n_cards, n_cards);
  assert(temp.n_cards == n_cards);
  return temp;
}

void test_print_hand() {
  printf("Testing print_hand(5)\n");
  deck_t deck = make_hand(5);
  print_hand(&deck);
  printf("\n");
}

bool test_deck_contains() {
  const char * const card_letters[] = {"2s", "Qs", "9h", "6d", "3c", "2h", "3s", "Qd", "Js", NULL};
  const int expected[9] = {1, 1, 1, 1, 1};
  // make deck containing 2s Qs 9h 6d 3c
  deck_t deck = make_hand(5);
  for(int i = 0; card_letters[i] != NULL; i++) {
    char value_letter = card_letters[i][0];
    char suit_letter = card_letters[i][1];
    card_t card = card_from_letters(value_letter, suit_letter);
    if(deck_contains(&deck, card) != expected[i]) {
      printf(" X: expected %d, got %d\n", expected[i], expected[i] == 0 ? 1 : 0);
      return false;
    } else {
      printf("OK: expected %d, got %d\n", expected[i], expected[i]);
    }
  }
  return true;
}

bool test_num_from_card_ptr() {
  for (unsigned i=0; i<52; i++) {
    card_t card = card_from_num(i);
    const card_t * cardptr = &card;
    unsigned n = num_from_card_ptr(cardptr); 
    if (n != i) {
      printf("\nERROR:\n");
      printf("Entered card num %d, got back card num %d\n", i, n);
      print_card(card);
      printf("\n");
      return false;
    } else {
      printf(".");
    }
  }
  printf("\n");
  return true;
}

int main(void) {
  if (!test_num_from_card_ptr()) {
    return EXIT_FAILURE;
  }
  test_print_hand();

  if (!test_deck_contains()) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
