#include <stdio.h>

int main(int argc, char* argv[]){
    printf("Please enter n, e and m: ");
    int n, e, m, res = 1;
    e = 0;

    if(scanf("%d %d %d", &n, &e, &m) == 3){
        res = modExp(n, e, m);
        /*int interN = n, interE = e;
        interN %= m;
        while (interE > 0) {
            if (interE & 1)
                res = res * interN % m;
            interN = interN * interN % m;
            interE >>= 1;
        }*/
        printf("%d ** %d mod %d = %d\n", n, e, m, res);
    /* TODO: Implement the pseudocode to do the modular exponentiation, and then printf it */
    } else{
        printf("You did not enter three integers. Exiting\n");
    }
    return 0;
}
int modExp(int n, int e, int m) {
    if (e == 1) return n % m;
    if (e & 1) return (n % m) * modExp(n * n % m, e / 2, m) % m;
    return modExp(n * n % m, e / 2, m) % m;
}