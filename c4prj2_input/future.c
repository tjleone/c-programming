#include <stdio.h>
#include "future.h"

// TODO: Add error message to void future_cards_from_deck(deck_t * deck, future_cards_t * fc)

/* This adds ptr into the future cards for the given index (that is, */
/* which ?n it is). So if this is a future card for ?3, then index */
/* will be 3.  ptr will point at an existing placeholder card */
/* (it will point into a hand at a card which was added */
/* with add_empty_card). */
/* Note that it is entirely possible to have an input like */
/*   Kh Qh As 4c 2c ?3 ?4 */
/*   Ac Qc As 4c 2c ?3 ?4 */
/* (which might happen if e.g., someone edited a file that */
/* originally have ?0, ?1, and ?2 but replaced them when */
/* they became known). Or you might see ?3 before ?2. */
/* Your add_future_card should handle such */
/* cases by reallocing its array to be large enough to handle */
/* the specified index, and just having empty decks for */
/* the indicies that have not had add_future_card called */
/* on them yet. */
void add_future_card(future_cards_t * fc, size_t index, card_t * ptr) {
  if (fc == NULL) {
    fprintf(stderr, "No memory allocated for future cards in future.c:add_future_card\n");
    return;
  }
  if (index >= fc->n_decks) {
    fc->decks =  (deck_t *)realloc(fc->decks, (index+1) * sizeof(*fc->decks));
    for (int i=fc->n_decks; i <= index; i++) {
      fc->decks[i].n_cards = 0;
      fc->decks[i].cards = NULL;
    }
    fc->n_decks = index + 1;
  }
  fc->decks[index].cards = (card_t **)realloc(fc->decks[index].cards, (fc->decks[index].n_cards+1)
					       * sizeof(*fc->decks[index].cards));
  fc->decks[index].n_cards++;
  fc->decks[index].cards[fc->decks[index].n_cards-1] = ptr;
}

   /* This function takes a deck (which has been shuffled), */
   /* and a future_cards_t (which has been filled in with */
   /* all the pointers to placeholders) and draws cards from */
   /* the deck and assigns their values and suits to the */
   /* placeholders pointed to in fc. */
   /* For example if the deck is */
   /*   As Kh 8c .... */
   /* and fc was created from the input */
   /*   3c 4c ?0 ?1 ?2 */
   /*   5h 9d ?0 ?1 ?2 */
   /* then this function will draw As for ?0, */
   /* and fill in the two placeholders for ?0 (which */
   /* you can find with the pointers in fc, as described */
   /* in the video).  Then it will draw Kh for ?1, */
   /* and so on. Think about a case where this function would need to */
   /* print an error message.  */
void future_cards_from_deck(deck_t * deck, future_cards_t * fc) {
  for(int i=0; i < fc->n_decks; i++) {
    //    if (fc->decks[i].n_cards > 0 && is_empty_card(fc->decks[i].cards[0])) {
    if (fc->decks[i].n_cards > 0) {
      card_t * c = deck->cards[i];
      for(int j=0; j < fc->decks[i].n_cards; j++) {
	fc->decks[i].cards[j]->value = c->value;
	fc->decks[i].cards[j]->suit = c->suit;
      }
    }
  }
}

void free_decks(deck_t * decks, int n_decks) {
  for (int i=0; i < n_decks; i++) {
    free(decks[i].cards);
  }
  free(decks);
}

// Free pointers to fc decks, and the **cards of each deck, but don't
// free pointers from **cards[index] to cards. Those pointers will be
// freed up when the hands are freed up.
void free_future_cards(future_cards_t * fc) {
  free_decks(fc->decks, fc->n_decks);
  free(fc);
}
