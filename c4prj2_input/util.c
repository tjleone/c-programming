#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"

// card_t card_from_letters(char value_let, char suit_let);
// card_t * make_empty_card(void);
// bool is_empty_card(card_t * c);
// void print_card(card_t c);
// void add_card_to(deck_t * deck, card_t c);
// card_t * add_empty_card(deck_t * deck); // uses make_empty_card() and add_card_to()
// void free_cards(deck_t * deck);
// void free_deck(deck_t * deck);
// void print_hand(deck_t * hand);

void strip_newline(char * str) {
  char * p = strchr(str, '\n');
  if (p != NULL) {
    *p = '\0';
  }
}

void add_card_from_letters_to(deck_t * deck, char value_let, char suit_let) {
  if (value_let == '?') {
    add_empty_card(deck);
  } else {
    card_t card = card_from_letters(value_let, suit_let);
    add_card_to(deck, card);
  }
}

void add_card_from_string_to(deck_t * deck, char *s) {
  assert(strlen(s) == 2);
  add_card_from_letters_to(deck, s[0], s[1]);
}

future_cards_t * make_empty_future_cards() {
  future_cards_t * fc = malloc(sizeof(*fc));
  fc->n_decks = 0;
  fc->decks = NULL;
  return fc;
}

void print_deck(deck_t * deck, int index) {
  for (int i=0; i < deck->n_cards; i++) {
    card_t card = *deck->cards[i];
    if (card.value == 0 && card.suit == 0) {
      char c = '0' + index;
      printf("?%c ", c);
    } else {
      print_card(card);
    }
    printf(" ");
  }
  printf("\n");
}

void print_future_cards(future_cards_t * fc) {
  printf("\nFuture cards-------------------------\n");
  for (int i=0; i < fc->n_decks; i++) {
    print_deck(&fc->decks[i], i);
  }
  printf("\n-------------------------------------\n");
  printf("\n");
}

deck_t * deck_from_string(char * deck_str) {
  deck_t * deck = make_empty_deck();
  strip_newline(deck_str);
  char delim[] = " ";
  char * token = strtok(deck_str, delim);

  while (token != NULL) {
    printf("Card string: %s\n", token);
    add_card_from_string_to(deck, token);
    token = strtok(NULL, delim);
  }
  return deck;
}
