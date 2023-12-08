#include <stdio.h>
#include <math.h>

int main()
{
   int n = 0, curr, sum = 0, squaresum = 0;     // number of values read
   float mu, sig; //the mean and standard deviation

   /* TODO (Q1): compute the mean and standard deviation of n integers
    * First read input (n integers) from the user till EOF (Ctrl-D)
    * Output the mean and standard deviation for the n numbers.  
    * You cannot use the built in math library functions for mean and sd.
   */
    while (scanf("%d", &curr) == 1) {
        ++n;
        sum += curr;
        squaresum += curr * curr;
    }
    mu = (float) sum / n;
    sig = sqrt((float) squaresum / n - mu * mu);
   printf("mu=%f sig=%f\n",mu,sig);
   return 0;
   
}
