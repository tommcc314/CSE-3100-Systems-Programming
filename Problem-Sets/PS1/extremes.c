// Min/Max
#include <stdio.h>
#include <math.h>
int main(int argc, char* argv[]){
    double x, min = INFINITY, max = -INFINITY;
    while(scanf("%lf", &x) == 1) {
        if (x < min) min = x;
        if (x > max) max = x;
        printf("Min=%lf Max=%lf\n", min, max);
    }
    return 0;
}
