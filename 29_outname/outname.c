#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  const char suffix[] = ".counts";
  char * outputName = malloc((strlen(inputName) + strlen(suffix) + 1) * sizeof(*outputName));
  strcpy(outputName, inputName);
  strcat(outputName, suffix);
  return outputName;
}
