#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

void stripNewline(char * str) {
  char * p = strchr(str, '\n');
  if (p != NULL) {
    *p = '\0';
  }
}

char * getValue(char * key, kvarray_t *kvPairs) {
  for(int i=0; i < kvPairs->numPairs; i++) {
    if(strcmp(key, kvPairs->pairs[i]->key) == 0) {
      return kvPairs->pairs[i]->value;
    }
  }
  return NULL;
}

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    perror("Could not open file for reading\n");
    return NULL;
  }
  counts_t * answer = createCounts();
  char * line = NULL;
  size_t sz = 0;
  while(getline(&line, &sz, f) >= 0) {
    stripNewline(line);
    addCount(answer, getValue(line, kvPairs));
    free(line);
    line = NULL;
  }
  free(line);
  fclose(f);
  return answer;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  if(argc < 3) {
    fprintf(stderr, "Usage: %s kvfn kfn1 [kfn2 ...]\n", argv[1]);
    fprintf(stderr, "\tkfn: name of file with key/value pairs\n");
    fprintf(stderr, "\tkfn1, kfn2, etc.: name of files with keys\n");
    return EXIT_FAILURE;
  }
  kvarray_t * kv = readKVs(argv[1]);

  char suffix[] = ".counts";
 //count from 2 to argc (call the number you count i)
  for(int i=2; i < argc; i++) {

    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);

    //compute the output file name from argv[i] (call this outName)
    char * outName = malloc(sizeof(*outName)
			    * (strlen(argv[i]) + strlen(suffix) + 1));
    strcpy(outName, argv[i]);
    strcat(outName, suffix);

    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    if (f == NULL) {
      perror("fopen");
      fprintf(stderr,"Trying to open %s\n", outName);
      abort();
    }

    //print the counts from c into the FILE f
    printCounts(c, f);

    //close f
    fclose(f);

    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }

 //free the memory for kv
    freeKVs(kv);

  return EXIT_SUCCESS;
}
