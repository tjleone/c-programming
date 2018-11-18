#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "cards.h"

const char suit_letters[NUM_SUITS] = "shdc";
const char value_letters[13] = "234567890JQKA";

void assert_value_valid(unsigned value) {
  assert(value >=2 && value <= VALUE_ACE);
}

void assert_suit_valid(suit_t suit) {
  assert(suit >= SPADES && suit <= CLUBS);
}

void assert_value_letter_valid(char value_letter) {
  assert(strchr(value_letters, value_letter));
}

void assert_suit_letter_valid(char suit_letter) {
  assert(strchr(suit_letters, suit_letter));
}

void assert_card_valid(card_t c) {
  assert_value_valid(c.value);
  assert_suit_valid(c.suit);
}

const char * ranking_to_string(hand_ranking_t r) {
  switch(r) {
  case STRAIGHT_FLUSH:
    return "STRAIGHT_FLUSH";
  case FOUR_OF_A_KIND:
    return "FOUR_OF_A_KIND";
  case FULL_HOUSE:
    return "FULL_HOUSE";
  case FLUSH:
    return "FLUSH";
  case STRAIGHT:
    return "STRAIGHT";
  case THREE_OF_A_KIND:
    return "THREE_OF_A_KIND";
  case TWO_PAIR:
    return "TWO_PAIR";
  case PAIR:
    return "PAIR";
  case NOTHING:
    return "NOTHING";
  default:
    printf("ranking_to_string: invalid hand ranking (%d)\n", r);  
    exit(EXIT_FAILURE);
  }
}

char value_letter(card_t c) {
  assert_value_valid(c.value);
  if (c.value >=2 && c.value <= 9) {
    return '0' + c.value;
  }
  switch(c.value) {
  case 10:
    return '0';
  case VALUE_JACK:
    return 'J';
  case VALUE_QUEEN:
    return 'Q';
  case VALUE_KING:
    return 'K';
  case VALUE_ACE:
    return 'A';
  default:
    printf("value_letter: invalid value (%d)\n", c.value);
    exit(EXIT_FAILURE);
  }
}


char suit_letter(card_t c) {
  assert_suit_valid(c.suit);
  if (c.suit < 0 || c.suit >= NUM_SUITS) {
    printf("suit_letter: invalid suit (%d)\n", c.suit);
    exit(EXIT_FAILURE);
  }
  return suit_letters[c.suit];
}

void print_card(card_t c) {
  assert_card_valid(c);
  printf("%c%c", value_letter(c), suit_letter(c));
}

unsigned value_from_letter(char value_let) {
  assert_value_letter_valid(value_let);
  if (value_let > '0' && value_let <= '9') {
    return value_let - '0';
  } else {
    switch(value_let) {
    case '0':
      return 10;
    case 'A':
      return VALUE_ACE;
    case 'K':
      return VALUE_KING;
    case 'Q':
      return VALUE_QUEEN;
    case 'J':
      return VALUE_JACK;
    default:
      printf("value_from_letter: invalid card value (%c)", value_let);
      exit(EXIT_FAILURE);
    }
  }
}

suit_t suit_from_letter(char suit_let) {
  assert_suit_letter_valid(suit_let);
  switch(suit_let) {
  case 's':
    return SPADES;
  case 'h':
    return HEARTS;
  case 'd':
    return DIAMONDS;
  case 'c':
    return CLUBS;
  default:
    printf("suit_from_letter: invalid card suit (%c)", suit_let);
    exit(EXIT_FAILURE);
  }
}

card_t card_from_letters(char value_let, char suit_let) {
  assert_value_letter_valid(value_let);
  assert_suit_letter_valid(suit_let);
  card_t temp;
  temp.value = value_from_letter(value_let);
  temp.suit = suit_from_letter(suit_let);
  assert_card_valid(temp);
  return temp;
}

card_t card_from_num(unsigned c) {
  assert(c >= 0 && c < 52);
  card_t temp;
  temp.value = c % 13 + 2;
  temp.suit = c / 13;
  return temp;
}

unsigned num_from_card_ptr(const card_t *c) {
  assert_card_valid(*c);
  return c->suit * 13 + c->value - 2;
}

int compare_cards_by_num(const void *c1vp, const void *c2vp) {
  const card_t * const *c1ptr = c1vp;
  const card_t * const *c2ptr = c2vp;
  return num_from_card_ptr(*c1ptr) - num_from_card_ptr(*c2ptr);
}

void swap_cards(card_t *c1, card_t *c2) {
  card_t temp = *c1;
  *c1 = *c2;
  *c2 = temp;
}

card_t * make_empty_card(void) {
  card_t * empty_card = malloc(sizeof(*empty_card));
  empty_card->value = EMPTY_CARD_VALUE;
  empty_card->suit = EMPTY_CARD_SUIT;
  return empty_card;
}

bool is_empty_card(card_t * c) {
  if (c == NULL) {
    return false;
  }
  return (c->value == EMPTY_CARD_VALUE) && (c->suit == EMPTY_CARD_SUIT);
}
