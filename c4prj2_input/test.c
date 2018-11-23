/* TODO: Write up tests for */
/*     deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) */
/* */
/* Common mistakes we have seen so far: */
/* not handling ?nums that are more than one digit (?10, ?11) */
/* not handling it properly if multiple draws are done for the hand */
/* not handling it properly if we sort the hand." */
/* */
/* "Note that it is entirely possible to have an input like */
/* Kh Qh As 4c 2c ?3 ?4 */
/* Ac Qc As 4c 2c ?3 ?4" */
/* "void future_cards_from_deck(deck_t * deck, future_cards_t * fc); */
/* Think about a case where this function would need to print an error message" */
/* "Note that most of the rest of the code assumes that a poker hand */
/* has AT LEAST 5 cards in it. Your read_input function should enforce */
/* this requirement. If there are fewer than 5 cards, print */
/*   a useful error message and exit. */
  
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "cards.h"
#include "deck.h"
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

void free_memory(deck_t * deckptr, deck_t * known_cards, future_cards_t * fc, deck_t ** decks, int n_hands) {

  //  printf("Calling free_deck\n");
  free_deck(deckptr);
  //  printf("...back from free_deck\n");

  //  printf("Calling free_cards\n");
  free_cards(known_cards);
  //  printf("...back from free_cards\n");

  //  printf("Calling free_future_cards\n");
  // doesn't free up **cards[index] pointers, which are
  // freed through the hands
  // free_future_cards(fc);
  // printf("...back from free_future_cards\n");

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

void test_read_input(FILE * f, FILE * fout) {
  future_cards_t unknown;
  unknown.n_decks = 0;
  unknown.decks = NULL;
  size_t n_hands = 0;
  //  printf("Calling read_input...\n");
  deck_t ** decks = read_input(f, &n_hands, &unknown);
  //  printf("...back from read_input with n_hands=%ld\n", n_hands);
  if(decks == NULL) {
    return;
  }
  future_cards_t * fc = &unknown;
  deck_t known_cards;
  known_cards.n_cards = 0;
  known_cards.cards = NULL;
  for (int deckno=0; deckno < n_hands; deckno++) {
    for (int i=0; i < decks[deckno]->n_cards; i++) {
      if(decks[deckno]->cards[i]->value + decks[deckno]->cards[i]->suit != 0) {
	add_card_to(&known_cards, *decks[deckno]->cards[i]);
      }
    }
  }
  //  printf("Calling make_deck_exclude...\n");
  deck_t * deckptr = make_deck_exclude(&known_cards);
  //  printf("...back from make_deck_exclude\n");
  //  printf("Calling shuffle...\n");
  shuffle(deckptr);
  //  printf("...back from shuffle\n");

  //  printf("Calling print_future_cards with fc->n_decks=%ld\n", fc->n_decks);
  //  print_future_cards(fc);
  //  printf("...back from print_future_cards\n");
  //  printf("Calling future_cards_from_deck\n");
  future_cards_from_deck(deckptr, fc);
  //  printf("...back from future_cards_from_deck\n");

  for(int i=0; i < n_hands; i++) {
    deck_t *hand = decks[i];
    sort_cards(hand->cards, hand->n_cards);
  }

  for(int i=0; i < n_hands; i++) {
    //    printf("Calling print_hand\n");
    //    print_hand(decks[i]);
    //    printf("\n");
    fprint_hand(fout, decks[i]);
    fprintf(fout,"\n");
    //    printf("...back from print_hand\n");
  }
  free_memory(deckptr, &known_cards, fc, decks, n_hands);
}

int main(int argc, char ** argv) {
  if(argc != 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return EXIT_FAILURE;
  }
  const char * in_suffix = ".txt";
  char * infilename = malloc(strlen(argv[1]) + strlen(in_suffix) + 1);
  if (infilename == NULL) {
    fprintf(stderr, "Couldn't create input file name\n");
    free(infilename);
    return EXIT_FAILURE;
  }
  strcpy(infilename, argv[1]);
  strcat(infilename, in_suffix);
  const char * out_suffix = "_result.txt";
  char * outfilename = malloc(strlen(argv[1]) + strlen(out_suffix) + 1);
  if (outfilename == NULL) {
    fprintf(stderr, "Couldn't create output file name\n");
    free(infilename);
    free(outfilename);
    return EXIT_FAILURE;
  }
  strcpy(outfilename, argv[1]);
  strcat(outfilename, out_suffix);
  FILE * fptr = fopen(infilename, "r");
  if (fptr == NULL) {
    perror("Failed to open the input file");
    fprintf(stderr, "Did you mean to call it %s?\n", infilename);
    free(infilename);
    free(outfilename);
    return EXIT_FAILURE;
  }
  FILE * fresult_ptr = fopen(outfilename, "w");
  if (fresult_ptr == NULL) {
    perror("Failed to open the output file");
    fprintf(stderr, "Did you mean to call it %s?\n", outfilename);
    free(infilename);
    free(outfilename);
    return EXIT_FAILURE;
  }
  
  //  test_add_future_card_test();
  //test_future_cards_from_deck();
  //test_deck_from_string();
  //test_hand_from_string();
  //test_future_cards_from_deck();
  test_read_input(fptr, fresult_ptr);
  free(infilename);
  free(outfilename);
  fclose(fptr);
  fclose(fresult_ptr);
  return EXIT_SUCCESS;
}
