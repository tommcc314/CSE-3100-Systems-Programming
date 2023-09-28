#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 2147483647
#define N 10000

#define RANDPOINT (1.0*(rand() % MAX)/MAX)
double DISTSQUARED(double x, double y) {
    return x * x + y * y;
}
bool SAMPLE() {
    return DISTSQUARED(RANDPOINT, RANDPOINT) <= 1.0;
}
int main(int argc, char* argv[]){
    srand(10);
    unsigned int j = 0;
    for(unsigned int i = 0; i < N; i++){
        if(SAMPLE()){
            j++;
        }
    }
    //printf("%d", j);
    double pi = 4.0*j/N;
    printf("pi: %lf\n", pi);
        
    return 0;
}