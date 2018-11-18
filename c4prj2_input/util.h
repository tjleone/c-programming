#ifndef UTIL_H
void strip_newline(char * str);
void add_card_from_letters_to(deck_t * deck, char value_let, char suit_let);
void add_card_from_string_to(deck_t * deck, char *s);
future_cards_t * make_empty_future_cards();
void print_deck(deck_t * deck, int index);
void print_future_cards(future_cards_t * fc);
deck_t * deck_from_string(char * deck_str);
#endif
