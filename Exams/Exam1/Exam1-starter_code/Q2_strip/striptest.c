#include "strip.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
   /* DO NOT MODIFY THIS PROGRAM */
   char* line = NULL;
   size_t len = 0;
   if (getline(&line,&len,stdin) == 0) {
      exit(1); // bad input
   }
   char* up = strip(line);
   printf("[%s]\n",up);
   free(line);
   return 0;
}
