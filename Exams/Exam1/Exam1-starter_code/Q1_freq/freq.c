#include <stdio.h>
#include <stdlib.h>
/* Q1. Implement the functions getMSDigit() and main() */

int getMSDigit(int x)
{
   while (x >= 10) {
      x /= 10;
   }
   return x;
}

int main()
{
   /* TODO: 
    * Read input from the stdin till EOF
    * For each integer, obtain the leading digit
    * Calculate the frequencies of the leading digits
    * Print the frequencies on stdout */
   int* freqs = calloc(10, sizeof(int));
   int temp;
   while (scanf("%d", &temp) == 1) {
      freqs[getMSDigit(temp)]++;
   }
   for (int i = 0; i < 10; ++i) {
      printf("%d:%d ", i, freqs[i]);
   }
   printf("\n");
   free(freqs);
   return 0;
}
