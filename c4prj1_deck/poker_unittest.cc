// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// A sample program demonstrating using Google C++ testing framework.

#include <limits.h>
extern "C" {
  #include "cards.h"
  #include "deck.h"
  #include "eval.h"
}
// Don't forget gtest.h, which declares the testing framework.
#include "gtest/gtest.h"
namespace {
  // Tests add_card_to().

  // Tests add_card_to with a full deck of cards.
  TEST(add_card_to_test, Full) {
    // This test is named "Full", and belongs to the "add_card_to_test"
    // test case.
    size_t n_cards = 4;
    deck_t temp;
    temp.cards = NULL;
    temp.n_cards = 0;
    int cardNo = 0;
    for(int i=0; i<n_cards && cardNo < 52; i++, cardNo+=52/n_cards) {
      printf("adding card number %d with value %d\n", i, cardNo);
      add_card_to(&temp, card_from_num(cardNo));
    }
    printf("temp.n_cards=%ld, n_cards=%ld\n", temp.n_cards, n_cards);
    EXPECT_EQ(temp.n_cards, n_cards);
    free_cards(&temp);
  }

  // Tests add_card_to with one card as input.
  TEST(add_card_to_test, One) {
    // This test is named "One", and belongs to the "add_card_to_test"
    // test case.
    size_t n_cards = 4;
    deck_t temp;
    temp.cards = NULL;
    temp.n_cards = 0;

    card_t card;
    card.value = VALUE_KING;
    card.suit = HEARTS;
    add_card_to(&temp, card);
    EXPECT_EQ(temp.n_cards, 1);
    EXPECT_EQ(temp.cards[0]->value, VALUE_KING);
    EXPECT_EQ(temp.cards[0]->suit, HEARTS);
    EXPECT_EQ(value_letter(*temp.cards[0]), 'K');
    EXPECT_EQ(suit_letter(*temp.cards[0]), 'h');
    free_cards(&temp);
  }

  // Tests add_empty_card()

  // Tests NULL input.
  TEST(add_empty_card_test, Null) {
    deck_t temp;
    temp.cards = NULL;
    temp.n_cards = 0;
    add_empty_card(&temp);
    EXPECT_EQ(temp.n_cards, 1);
    free_cards(&temp);
  }
  // Tests make_deck_exclude().

  // Tests make_deck_exclude with a deck of excluded cards.
  TEST(make_deck_exclude_test, Full) {
    // This test is named "Full", and belongs to the "add_card_to_test"
    // test case.
    deck_t excluded;
    excluded.cards = NULL;
    excluded.n_cards = 0;
    int cardNo = 0;
    for(int i=0; cardNo < 52; i++, cardNo=i*i) {
      printf("adding card number %d with value %d\n", i, cardNo);
      add_card_to(&excluded, card_from_num(cardNo));
    }
    deck_t * deck = make_deck_exclude(&excluded);
    // Excludes cards numbered 0, 1, 4, 9, 16, 25, 36, 49
    EXPECT_EQ(deck->n_cards, 44); // 8 cards are excluded, so should be 44 in temp
    free_cards(&excluded);
    free_deck(deck);
  }

  // Tests build_remaining_deck().

  // Tests build_remaining_deck with a deck of excluded cards.
  TEST(build_remaining_deck_test, Full) {
    // This test is named "Full", and belongs to the "add_card_to_test"
    // test case.
    size_t n_hands = 2;
    deck_t * hand1 = (deck_t *)malloc(sizeof(*hand1));
    deck_t * hand2 = (deck_t *)malloc(sizeof(*hand2));
    deck_t ** hands = (deck_t **)malloc(n_hands * sizeof(**hands));
    card_t card;

    const char * hand1_strings[] = {"Kh", "Qs", "?0", "?1", "?2", "?3", "?4", NULL};
    const char * hand2_strings[] = {"As", "Ac", "?0", "?1", "?2", "?3", "?4", NULL};
    
    hand1->cards = NULL;
    hand1->n_cards =0;
    for(int i=0; hand1_strings[i] != NULL; i++) {
      if (hand1_strings[i][0] == '?') {
	add_empty_card(hand1);
      } else {
	printf("Adding valid card %s\n", hand1_strings[i]);
	card = card_from_letters(hand1_strings[i][0], hand1_strings[i][1]);
	printf("Added card with value %d, suit %d\n", card.value, card.suit);
	add_card_to(hand1, card);
      }
      hand1->n_cards = i+1;
    }
    
    hand2->cards = NULL;
    hand2->n_cards =0;
    for(int i=0; hand2_strings[i] != NULL; i++) {
      if (hand2_strings[i][0] == '?') {
	add_empty_card(hand2);
      } else {
	printf("Adding valid card %s\n", hand2_strings[i]);
	card = card_from_letters(hand2_strings[i][0], hand2_strings[i][1]);
	printf("Added card with value %d, suit %d\n", card.value, card.suit);
	add_card_to(hand2, card);
      }
      hand2->n_cards = i+1;
    }
    hands[0] = hand1;
    hands[1] = hand2;

    for(int i=0; i < n_hands; i++) {
      printf("hands %d has %ld cards\n", i, hands[i]->n_cards);
    }

    deck_t * deck = build_remaining_deck(hands, n_hands);
    EXPECT_EQ(deck->n_cards, 48); // 4 cards are excluded, so should be 48 in deck
    for(int i=0; i < n_hands; i++) {
      free_deck(hands[i]);
    }
    free(hands);
    free_deck(deck);
  }
  
}  // namespace
