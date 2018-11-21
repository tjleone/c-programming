#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "cards.h"
#include "deck.h"
#include "future.h"
#include "input.h"

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
    printf("?%d ", i);
  }
  printf("\n");
  for (int i=0; i < fc->n_decks; i++) {
    printf("?%d: %ld\n", i, fc->decks[i].n_cards);
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
    add_card_from_string_to(deck, token);
    token = strtok(NULL, delim);
  }
  return deck;
}

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
    if (answer[n_decks-1] == NULL) {
      for (int i = 0; i < n_decks-1; i++) {
	free_deck(answer[i]);
      }
      free(answer);
      free(line);
      *n_hands = 0;
      return NULL;
    }
  }
  free(line);
  *n_hands = n_decks;
  return answer;
}

// recommended in README for input.c
deck_t * hand_from_string(const char * str, future_cards_t * fc) {
  deck_t * deck = make_empty_deck();
  char * hand_str = strdup(str); // can't call strtok on a const char *
  const char delim[] = " \n";
  char * token = strtok(hand_str, delim);
  int n_cards = 0;

  while (token != NULL) {
    assert(strlen(token) > 1);
    if (token[0] == '?') {
      // add empty card deck
      card_t * cptr = add_empty_card(deck);
      // number following '?' might have more than one digit
      size_t index = strtol(&token[1], NULL, 0);
      // add a pointer to the empty card to fc
      add_future_card(fc, index, cptr);
    } else {
      add_card_from_string_to(deck, token);
    }
    n_cards++;
    token = strtok(NULL, delim);
  }

  if(n_cards < 5) {
    fprintf(stderr, "At least five cards per hand needed. %d cards found.\n", n_cards);
    
    for (int i=0; i < fc->n_decks; i++) {
      if (fc->decks[i].n_cards > 0) {
	free(fc->decks[i].cards);
	fc->decks[i].cards = NULL;
      }
    }
    free(fc->decks);
    free_deck(deck);
    free(hand_str);
    return NULL;
  }

  free(hand_str);
  return deck;
}
