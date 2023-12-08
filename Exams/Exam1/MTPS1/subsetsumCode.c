#include "subsetsum.h"
#include <stdio.h>
#include <stdlib.h>
/* 
 * This function has 3 inputs and will produce on stdout the list of subsetsum in lexicographic
 * increasing order
 * n : the number of integers in the input set
 * s : the target sum to reach 
 * t : an array of size n with the integers present in the input set.
 * output: none. Only side-effects on the standard output
 */ 
void traverseSubsets(int n, int s, int t[n], int m, int x, int ss[n]) {
   if (s == 0) {
      printf("sss: [");
      for (int i = 0; i < m; ++i) {
         printf("%d ", ss[i]);
      }
      printf("] \n");
   }
   else if (s > 0) {
      for (int i = x; i < n; ++i) {
         // int* newss = malloc(n * sizeof(int));
         // for (int j = 0; j < m; ++j) {
         //    newss[j] = ss[j];
         // }
         ss[m] = t[i];
         traverseSubsets(n, s - t[i], t, m + 1, i + 1, ss);
      }
   }
}
void subSetSum(int n,int s,int t[n])
{
   // TODO(Q2.1): Implement this routine
   int* ss = malloc(n * sizeof(int));
   traverseSubsets(n, s, t, 0, 0, ss);
   free(ss);
}

