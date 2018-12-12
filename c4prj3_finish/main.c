#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

int strtoi(const char *buff) {
  char *end;
  int si = -1;

  errno = 0;

  const long sl = strtol(buff, &end, 10);

  if (end == buff) {
    fprintf(stderr, "%s: not a decimal number\n", buff);
  } else if ('\0' != *end) {
    fprintf(stderr, "%s: extra characters at end of input: %s\n", buff, end);
  } else if ((LONG_MIN == sl || LONG_MAX == sl) && ERANGE == errno) {
    fprintf(stderr, "%s out of range of type long\n", buff);
  } else if (sl > INT_MAX) {
    fprintf(stderr, "%ld greater than INT_MAX\n", sl);
  } else if (sl < INT_MIN) {
    fprintf(stderr, "%ld less than INT_MIN\n", sl);
  } else {
    si = (int)sl;
  }
  return si;
}

void free_hands(deck_t ** hands, size_t n_hands) {
  for (int i = 0; i < n_hands; i++) {
    free_deck(hands[i]);
  }
  free(hands);
}

void free_fcs(future_cards_t * fc) {
  for(int i=0; i < fc->n_decks; i++) {
    free(fc->decks[i].cards);
  }
  free(fc->decks);
  free(fc);
}

void free_strings(char ** strings, int n_strings) {
  for(int i=0; i < n_strings; i++) {
    free(strings[i]);
  }
  free(strings);
}

char ** make_test_filenames(int n_filenames) {
  const char * test_dir = "/home/tj/learn2prog/c4prj3_finish/provided-tests/";
  char ** test_filenames = malloc(n_filenames*sizeof(*test_filenames));
  int sz = strlen(test_dir) + strlen("test00.txt") + 1;
  for(int i=0; i < n_filenames; i++) {
    char * filename = malloc(sz*sizeof(*filename));
    sprintf(filename, "%stest%02d.txt", test_dir, i+1);
    test_filenames[i] = filename;
  }
  return test_filenames;
}

char ** make_answers(int n_answers) {
  char ** answers = malloc(n_answers*sizeof(*answers));
  FILE * f = fopen("provided-tests/answers.txt","r");
  if (f == NULL) {
    perror("Failed to open the answers.txt file");
    return NULL;
  }
  char * line = NULL;
  size_t sz = 0;
  for (int i=0; i < n_answers && getline(&line, &sz, f) > 0; i++) {
    answers[i] = strdup(line);
  }
  while(getline(&line, &sz, f) > 0) {
    answers[n_answers-1] = realloc(answers[n_answers-1],
				   strlen(answers[n_answers-1])
				   + strlen(line) + 1);
    strcat(answers[n_answers-1], line);
  }
  free(line);
  fclose(f);

  return answers;
}

void do_trial(int trial_n, deck_t ** hands, int n_hands, deck_t * remaining_deck, future_cards_t * fc, int * wins) {
  shuffle(remaining_deck);
  future_cards_from_deck(remaining_deck, fc);
  int winning_hand_n = 0;
  for(int i=1; i < n_hands; i++) {
    if(compare_hands(hands[winning_hand_n], hands[i]) < 0) {
      winning_hand_n = i;
    }
  }

  // Check for a tie
  for(int i=0; i < n_hands; i++) {
    if(i != winning_hand_n && !compare_hands(hands[winning_hand_n], hands[i])) {
      winning_hand_n = n_hands;
      break;
    }
  }
  wins[winning_hand_n]++;
}

char * get_answer(FILE *f, int n_trials) {
  // Read the hands in the input file
  future_cards_t * fc = malloc(sizeof(*fc));
  fc->n_decks = 0;
  fc->decks = NULL;
  size_t n_hands = 0;

  deck_t ** hands = read_input(f, &n_hands, fc);
  deck_t * remaining_deck = build_remaining_deck(hands, n_hands);

  // Create an array to count how many times each hand
  // wins, with one more element for if there was a tie
  // (so if there are 2 hands, you should have 3 elements)
  // and initialize all its values to 0.
  int *wins = malloc((n_hands+1)*sizeof(*wins));
  for(int i=0; i<=n_hands; i++) {
    wins[i] = 0;
  }

  for(int i=0; i<n_trials; i++) {
    do_trial(i, hands, n_hands, remaining_deck, fc, wins);
  }
  int result_str_len = 256;
  char * result_str = malloc(result_str_len*sizeof(*result_str));
  int length = 0;
  for(size_t i=0; i<n_hands; i++) {
    if(strlen(result_str) + 80 > result_str_len) {
      result_str_len += 80;
      result_str = realloc(result_str, result_str_len*sizeof(*result_str));
    }

    length += sprintf(result_str+length,
		      "Hand %zu won %u / %u times (%.2f%%)\n",
		      i, wins[i], n_trials, (double)wins[i]*100/n_trials);
  }
  length += sprintf(result_str+length, "And there were %u ties\n", wins[n_hands]);  
  free(wins);
  free_hands(hands, n_hands);
  free_fcs(fc);
  free_deck(remaining_deck);

  return result_str;
}

struct expected_tag {
  char * filename;
  char * answer;
};
typedef struct expected_tag expected_t;

void free_expected(expected_t * expected, int n_expected) {
  for(int i=0; i < n_expected; i++) {
    free(expected[i].filename);
    free(expected[i].answer);
  }
  free(expected);
}

expected_t * make_expected(const int n_filenames) {
  int n_answers = n_filenames;
  char ** filenames = make_test_filenames(n_filenames);
  char ** answers = make_answers(n_answers);
  expected_t * expected = malloc(n_filenames*sizeof(*expected));

  for(int i=0; i < n_filenames; i++) {
    expected[i].filename = strdup(filenames[i]);
    expected[i].answer = strdup(answers[i]);
  }

  free_strings(filenames, n_filenames);
  free_strings(answers, n_filenames);
  return expected;
}

char * get_expected_answer(char * filename, expected_t * expected, const int n_filenames) {
  for(int i=0; i<n_filenames; i++) {
    if (!strcmp(filename, expected[i].filename)) {
      return expected[i].answer;
    }
  }
  fprintf(stderr, "File name %s not found\n", filename);

  return NULL;
}

int do_it(char * filename, FILE *f, size_t n_trials) {
  const int n_filenames = 16;
  expected_t * expected = make_expected(n_filenames);
  char * expected_answer = get_expected_answer(filename, expected, n_filenames);
  char * actual_answer = get_answer(f, n_trials);

  printf("%s", actual_answer);

  free_expected(expected, n_filenames);
  if (expected_answer == NULL) {
    return EXIT_FAILURE;
  }
  if (actual_answer == NULL) {
    return EXIT_FAILURE;
  }
  free(actual_answer);
  return EXIT_SUCCESS;
}

int main(int argc, char ** argv) {
  int n_trials = 10000;
  // Check command line arguments/report errors
  if(argc < 2) {
    fprintf(stderr, "Usage: %s <filename> [number of trials]\n", argv[0]);
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1],"r");
  if (f == NULL) {
    perror("Failed to open the input file");
    fprintf(stderr, "Did you mean to call it %s?\n", argv[1]);
    return EXIT_FAILURE;
  }
  if (argc > 2) {
    n_trials = strtoi(argv[2]);
    if (n_trials == -1) {
      return EXIT_FAILURE;
    }
  }
  //  return do_it(f, n_trials);
  int retval = do_it(argv[1], f, n_trials);
  fclose(f);
  return retval;
}
