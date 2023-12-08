#include <stdio.h>
#include <stdlib.h>
#include "subsetsum.h"
/* Q4: Write a program that computes all the subset sums for a given list of integers. 
   Input:  <n> <s> <a0> <a1> .... <a_{n-1}> 
   output: sss:[<a_00> ... <a_0k> ]
           ...
           sss:[<a_i0> ... <a_ij> ]

   Namely, one can produce the sum <s> using <i>+1 different subsets of the <n> numbers
   <a_0> ... <a_{n-1}>. Subset 0 uses <k> numbers while subset <i> uses <j> integers. 

   Example:
   Input:
   4 10 1 9 7 2
   Ouptut:
   sss:[1 9 ]
   sss:[1 7 2 ]

   Namely, there are two ways to produce 10. One with the subset 1 9, the other with 
   subset 1 7 2

   Think carefully of the corner cases. We will check your code with valgrind.
*/

int main(int argc,char* argv[])   
{
   // TODO(Q2.2): implement the test program
   // read the input from the standard input according to the rules shown above
   // Then invoke your subSetSum to find and print all the subsets
    int n, s;
    scanf("%d", &n);
    scanf("%d", &s);
    int* t = malloc(n * sizeof(int));
    int x = 0;
    while (scanf("%d", &t[x]) == 1) {
        ++x;
    }
    subSetSum(n, s, t);
    free(t);
    return 0;
}