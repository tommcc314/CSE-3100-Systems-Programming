#include <stdio.h>
#include <math.h>
double relError(double x, double s){
    return fabs(x * x - s) / s;
}

int main(int argc, char* argv[]){
    double s;
    printf("Enter S to take square root of: ");
    scanf("%lf", &s);
    double guess = 1;
    while (guess * guess < s)
        guess++;
    while (relError(guess, s) >= 0.001)
        guess = (guess + s / guess) / 2.0;
    printf("Square root: %f\n", guess);
    return 0;
}