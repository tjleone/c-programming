#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>
#include "deck.h"

const int FULL_DECK_SIZE = 52;

//   Add the particular card to the given deck (which will
//   involve reallocing the array of cards in that deck).
void add_card_to(deck_t * deck, card_t c) {
  assert(deck != NULL);
  card_t * card = malloc(sizeof(*card));
  assert(card != NULL);
  card->value = c.value;
  card->suit = c.suit;

  deck->n_cards++;
  deck->cards = realloc(deck->cards, deck->n_cards*sizeof(*deck->cards));
  deck->cards[deck->n_cards-1] = card;
}

//   Add a card whose value and suit are both 0, and return a pointer
//   to it in the deck.
//   This will add an invalid card to use as a placeholder
//   for an unknown card.
card_t * add_empty_card(deck_t * deck) {
  assert(deck != NULL);
  card_t * empty_card = make_empty_card();
  add_card_to(deck, *empty_card);
  free(empty_card); // add_card_to adds a copy of *empty_card, so we have to free empty_card
  return deck->cards[deck->n_cards-1];
}

//   Create a deck that is full EXCEPT for all the cards
//   that appear in excluded_cards.  For example,
//   if excluded_cards has Kh and Qs, you would create
//   a deck with 50 cards---all of them except Kh and Qs.
//   You will need to use malloc to allocate this deck.
//   (You will want this for the next function).
//   Don't forget you wrote card_t card_from_num(unsigned c)
//   in Course 2 and int deck_contains(deck_t * d, card_t c)
//   in Course 3!  They might be useful here.
deck_t * make_deck_exclude(deck_t * excluded_cards) {
  deck_t * answer = malloc(sizeof(*answer));
  card_t card;
  answer->cards = NULL;
  answer->n_cards = 0;

  for(int i=0; i < 52; i++) {
    card = card_from_num(i);
    if (!deck_contains(excluded_cards, card)) {
      add_card_to(answer, card);
    }
  }
  return answer;
}

//   This function takes an array of hands (remember
//   that we use deck_t to represent a hand).  It then builds
//   the deck of cards that remain after those cards have
//   been removed from a full deck.  For example, if we have
//   two hands:
//      Kh Qs ?0 ?1 ?2 ?3 ?4
//      As Ac ?0 ?1 ?2 ?3 ?4
//   then this function should build a deck with 48
//   cards (all but As Ac Kh Qs).  You can just build
//   one deck with all the cards from all the hands
//   (remember you just wrote add_card_to),
//   and then pass it to make_deck_exclude.
deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) {
  deck_t temp;
  temp.cards = NULL;
  temp.n_cards = 0;
  for (int i=0; i < n_hands; i++) {
    for (int j=0; j < hands[i]->n_cards; j++) {
      if (!is_empty_card(hands[i]->cards[j])) {
	add_card_to(&temp, *hands[i]->cards[j]);
      }
    }
  }

  deck_t * answer = make_deck_exclude(&temp);
  free_cards(&temp);
  return answer;
}

void free_cards(deck_t * deck) {
  for(int i=0; i < deck->n_cards; i++) {
    free(deck->cards[i]);
  }
  free(deck->cards);
  deck->n_cards = 0;
  deck->cards = NULL;
}

//   Free the memory allocated to a deck of cards.
//   For example, if you do
//     deck_t * d = make_excluded_deck(something);
//     free_deck(d);
//   it should free all the memory allocated by make_excluded_deck.
//   Once you have written it, add calls to free_deck anywhere you
//   need to to avoid memory leaks.
void free_deck(deck_t * deck) {
  free_cards(deck);
  free(deck);
}

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

deck_t * make_empty_deck() {
  deck_t * deck = malloc(sizeof(*deck));
  deck->n_cards = 0;
  deck->cards = NULL;
  return deck;
}

void sort_cards(card_t ** array, size_t nelements) {
  qsort(array, nelements, sizeof(const card_t *), card_ptr_comp);
}
