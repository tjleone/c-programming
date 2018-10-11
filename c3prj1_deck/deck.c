#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "deck.h"
#include "eval.h"

const int FULL_DECK_SIZE = 52;

void print_hand(deck_t * hand){
  for(int i=0; i<hand->n_cards; i++) {
    print_card(hand->cards[i][0]);
    printf(" ");
  }
}

/*
   This function should check if a deck
   contains a particular card or not.  If
   the deck does contain the card, this
   function should return 1.  Otherwise,
   it should return 0.
   (You will use this later to
   build the deck of remaining cards
   which are not in any player's hand).
 */
int deck_contains(deck_t * d, card_t c) {
  for(int i=0; i<d->n_cards; i++) {
    const card_t * deck_card_ptr = d->cards[i];
    const card_t * target_card_ptr = &c;
    if(card_ptr_comp(&deck_card_ptr, &target_card_ptr) == 0) {
      return 1;
    }
  }
  return 0;
}

void shuffle(deck_t * d){
  for(int i=0; i<d->n_cards; i++) {
    swap_cards(d->cards[i], d->cards[rand() % d->n_cards]);
  }
}

void assert_full_deck(deck_t * d) {
  assert(d->n_cards == FULL_DECK_SIZE);
  for(unsigned i=0; i<FULL_DECK_SIZE; i++) {
    bool is_card_in_deck = deck_contains(d, card_from_num(i));
    assert(is_card_in_deck);
  }
}

void sort_cards(card_t ** array, size_t nelements) {
  qsort(array, nelements, sizeof(const card_t *), card_ptr_comp);
}
