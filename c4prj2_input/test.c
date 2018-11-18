#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

  future_cards_t * add_future_cards_from_card_string(char * card_string, deck_t * hand, future_cards_t * fc) {
    printf("\nadd_future_cards_from_card_string\n\n");

    card_t * cptr = add_empty_card(hand);
    size_t fc_index = card_string[1] - '0';
    add_future_card(fc, fc_index, cptr);
    return fc;
  }

  future_cards_t * add_card_from_string(char * card_string, deck_t * hand, future_cards_t * fc) {
    printf("\nadd_card_from_string\n\n");

    card_t card;
    if (card_string[0] == '?') {
      fc = add_future_cards_from_card_string(card_string, hand, fc);
    } else {
      printf("Adding valid card %s\n", card_string);
      card = card_from_letters(card_string[0], card_string[1]);
      printf("Added card with value %d, suit %d\n", card.value, card.suit);
      add_card_to(hand, card);
    }

    return fc;
  }

deck_t * add_card_to_deck(const char * card_string, deck_t * deck) {
    printf("\nadd_card_to_deck\n\n");
    card_t card;
    if (card_string[0] == '?') {
      add_empty_card(deck);
    } else {
      printf("Adding valid card %s\n", card_string);
      card = card_from_letters(card_string[0], card_string[1]);
      printf("Added card with value %d, suit %d\n", card.value, card.suit);
      add_card_to(deck, card);
    }
    return deck;
}

future_cards_t * add_deck_to_future_cards(deck_t * deck, size_t index, future_cards_t * fc) {
    printf("\nadd_deck_to_future_cards\n\n");
  if (index >= fc->n_decks) {
    fc->decks =  (deck_t *)realloc(fc->decks, (index+1) * sizeof(*fc->decks));
    fc->n_decks = index + 1;
  }
  fc->decks[index] = *deck;
  return fc;
}

deck_t * create_deck_from_strings(const char **strings) {
    printf("\ncreate_deck_from_strings\n\n");
      deck_t * hand = (deck_t *)malloc(sizeof(*hand));
      hand->n_cards = 0;
      hand->cards = NULL;

      for(int i = 0; strings[i] != NULL; i++){
	printf("strings[%d] is %s\n", i, strings[i]);
        hand = add_card_to_deck(strings[i], hand);
      }
      return hand;
}

  // Tests add_future_card with a deck of excluded cards.
void test_add_future_card_test() {
    // This test is named "Full", and belongs to the "add_future_card_test"
    // test case.
    
    const size_t N_HANDS = 2;
    const size_t N_CARDS_PER_HAND = 7;

    future_cards_t * fc = (future_cards_t *)malloc(sizeof(*fc));
    deck_t ** hands = (deck_t **)malloc(N_HANDS * sizeof(**hands));

    fc->n_decks = 0;
    fc->decks = NULL;
    
    int i, j;
    //    char string_matrix[N_HANDS][N_CARDS_PER_HAND][3] = {
    char string_matrix[2][7][3] = {
      {"Kh", "Qh", "As", "4c", "2c", "?3", "?4"},
      {"Ac", "Qc", "As", "4c", "2c", "?3", "?4"},
    };

    for(i = 0; i < N_HANDS; i++){
      deck_t * hand = (deck_t *)malloc(sizeof(*hand));
      hand->n_cards = 0;
      hand->cards = NULL;
      hands[i] = hand;
      for(j = 0; j < N_CARDS_PER_HAND; j++){
	printf("matrix[%d][%d] is %s\n", i, j, string_matrix[i][j]);
        fc = add_card_from_string(string_matrix[i][j], hands[i], fc);
      }
    }

    for(int i=0; i < N_HANDS; i++) {
      printf("hands %d has %ld cards\n", i, hands[i]->n_cards);
    }

    //    EXPECT_EQ(deck->n_cards, 48); // 4 cards are excluded, so should be 48 in deck
    for(int i=0; i < fc->n_decks; i++) {
      free_cards(&fc->decks[i]);
    }
    free(fc->decks);
    free(fc);

    for(int i=0; i < N_HANDS; i++) {
      free_deck(hands[i]);
    }
    free(hands);
  }

void test_deck_from_string(void) {
  char hand1[] = "3c 4c ?0 ?1 ?2";
  char hand2[] = "5h 9d ?0 ?1 ?2";
  deck_t * deck1 = deck_from_string(hand1);
  deck_t * deck2 = deck_from_string(hand2);
  printf("Printing deck for %s\n", hand1);
  print_deck(deck1, 0);
  printf("Printing deck for %s\n", hand2);
  print_deck(deck2, 1);
  
  free_deck(deck1);
  free_deck(deck2);
}

void test_hand_from_string(void) {
  future_cards_t * fc = make_empty_future_cards();
  //  char hand1[] = "3c 4c ?0 ?1 ?2";
  //char hand2[] = "5h 9d ?0 ?1 ?2";
  const char hand1[] = "Kh Qh As 4c 2c ?3 ?4";
  const char hand2[] = "Ac Qc As 4c 2c ?3 ?4";
  deck_t * deck1 = hand_from_string(hand1, fc);
  deck_t * deck2 = hand_from_string(hand2, fc);
  printf("Printing deck for %s\n", hand1);
  print_deck(deck1, 0);
  printf("Printing deck for %s\n", hand2);
  print_deck(deck2, 1);
  print_future_cards(fc);

  // doesn't free up **cards[index] pointers, which are
  // freed through the hands
  free_future_cards(fc);

  // Now free up the hands, which will free up the cards
  // pointers
  free_deck(deck1);
  free_deck(deck2);
}

void test_future_cards_from_deck(void) {
  future_cards_t * fc = make_empty_future_cards();
  //  char hand1[] = "3c 4c ?0 ?1 ?2";
  //char hand2[] = "5h 9d ?0 ?1 ?2";
  char hand1[] = "Kh Qh As 4c 2c ?3 ?4";
  char hand2[] = "Ac Qc As 4c 2c ?3 ?4";
  deck_t * deck1 = hand_from_string(hand1, fc);
  deck_t * deck2 = hand_from_string(hand2, fc);
  deck_t known_cards;
  known_cards.n_cards = 0;
  known_cards.cards = NULL;
  for (int i=0; i < deck1->n_cards; i++) {
    if(deck1->cards[i]->value + deck1->cards[i]->suit != 0) {
      add_card_to(&known_cards, *deck1->cards[i]);
    }
  }
  for (int i=0; i < deck2->n_cards; i++) {
    if(deck2->cards[i]->value + deck2->cards[i]->suit != 0) {
      add_card_to(&known_cards, *deck2->cards[i]);
    }
  }
  shuffle(&known_cards);
  deck_t * deckptr = make_deck_exclude(&known_cards);
  printf("Printing deck for %s\n", hand1);
  print_deck(deck1, 0);
  printf("Printing deck for %s\n", hand2);
  print_deck(deck2, 1);
  print_future_cards(fc);
  future_cards_from_deck(deckptr, fc);
  future_cards_from_deck(deckptr, fc);
  free_deck(deckptr);
  free_cards(&known_cards);
  // doesn't free up **cards[index] pointers, which are
  // freed through the hands
  free_future_cards(fc);

  // Now free up the hands, which will free up the cards
  // pointers
  free_deck(deck1);
  free_deck(deck2);
}

int main(void) {
  //  test_add_future_card_test();
  //test_future_cards_from_deck();
  //test_deck_from_string();
  //test_hand_from_string();
  test_future_cards_from_deck();
  
  return EXIT_SUCCESS;
}
