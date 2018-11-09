#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

kvpair_t * readKV(FILE *f) {
  char *line = NULL;
  size_t sz = 0;
  if (f == NULL) {
    return NULL;
  }

  if (getline(&line, &sz, f) <= 0) {
    free(line);
    return NULL;
  }

  char * p = strchr(line, '=');
  if (p == NULL) {
    fprintf(stderr, "Not a key=value pair: %s", line);
    return NULL;
  }
  // Notice that you will only need to free
  // answer->key to free the malloc'd block
  // that includes answer-key and answer-value
  kvpair_t * answer = malloc(sizeof(*answer));
  *p = '\0';
  answer->key = line;
  p++;
  char * end = strchr(p, '\n');
  if (end != NULL) {
    *end = '\0';
  }
  answer->value = p;
  return answer;
}

// In readKVs, you will want to open the file, read the lines of text, split them into
// key/value pairs, add the resulting pairs to an array (hint: realloc it to make it larger
// each time), close the file, and return the kvarray_t * that has your array.
// 
// Remember that you will want to abstract out complex steps into functions (you should
//see at least 2 pieces to naturally pull out into their own functions).

kvarray_t * readKVs(const char * fname) {
  FILE *f = fopen(fname, "r");
  if (f == NULL) {
    perror("Could not open file for reading\n");
    return NULL;
  }
  kvarray_t * answer = malloc(sizeof(*answer));
  answer->numPairs = 0;
  answer->pairs = NULL;
  kvpair_t * pair = NULL;
  while((pair = readKV(f)) != NULL) {
    answer->numPairs++;
    answer->pairs = realloc(answer->pairs,
			    answer->numPairs
			    * sizeof(*answer->pairs));
    answer->pairs[answer->numPairs - 1] = pair;
  }
  fclose(f);
  return answer;
}

//Next, you will write freeKVs, which should free all the memory allocated by readKVs.
//That is,  freeKVs(readKVs(filename)) should not leak any memory.
void freeKVs(kvarray_t * pairs) {
  for(int i=0; i < pairs->numPairs; i++) {
    free(pairs->pairs[i]->key); // value is part of the same block
    free(pairs->pairs[i]);
  }
  free(pairs->pairs);
  free(pairs);
}

// Third, write printKVs which should take a kvarray_t *, and print out
// 
//   "key = '%s' value = '%s'\n"
// for each key/value pair in the array, with the first %s being whatever the key is,
// and the second being whatever value (e.g., key = 'Jean Luc Picard' value = 'Captain').
void printKVs(kvarray_t * pairs) {
  for(int i=0; i < pairs->numPairs; i++) {
    printf("key = '%s' value = '%s'\n",
	   pairs->pairs[i]->key,
	   pairs->pairs[i]->value);
  }
}

//Finally, write the lookupValue function, which takes a kvarray_t * and a char * (string).
//The char * that is passed in represents a key.  This function searches the kvarray_t 
//for a matching key, and if found, returns the corresponding value.  If no match is found,
//this function returns NULL.
char * lookupValue(kvarray_t * pairs, const char * key) {
  for (int i=0; i < pairs->numPairs; i++) {
    if (strcmp(pairs->pairs[i]->key,key) == 0) {
      return pairs->pairs[i]->value;
    }
  }
  return NULL;
}
