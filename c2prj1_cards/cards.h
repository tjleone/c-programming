#ifndef CARD_H
#include <limits.h>
#include <stdbool.h>
#define CARD_H
#define VALUE_ACE 14
#define VALUE_KING 13
#define VALUE_QUEEN 12
#define VALUE_JACK 11
typedef enum {
  SPADES,
  HEARTS,
  DIAMONDS,
  CLUBS,
  NUM_SUITS
} suit_t;

#define EMPTY_CARD_VALUE INT_MIN
#define EMPTY_CARD_SUIT NUM_SUITS

struct card_tag {
  unsigned value;
  suit_t suit;
};
typedef struct card_tag card_t;
typedef enum {
  STRAIGHT_FLUSH,
  FOUR_OF_A_KIND,
  FULL_HOUSE,
  FLUSH,
  STRAIGHT,
  THREE_OF_A_KIND,
  TWO_PAIR,
  PAIR,
  NOTHING
} hand_ranking_t;
card_t card_from_num(unsigned c);
void assert_card_valid(card_t c);
const char * ranking_to_string(hand_ranking_t r) ;
char value_letter(card_t c);
char suit_letter(card_t c) ;
void print_card(card_t c);
card_t card_from_letters(char value_let, char suit_let);

unsigned num_from_card_ptr(const card_t *c);
int compare_cards_by_num(const void *c1vp, const void *c2vp);
int compare_cards(const void *c1vp, const void *c2vp);
void swap_cards(card_t *c1, card_t *c2);

card_t * make_empty_card(void);
bool is_empty_card(card_t * c);
#endif
