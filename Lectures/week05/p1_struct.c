/* Accessing elements of a struct */

typedef struct Mono {
    int coef;
    int deg;
    struct Mono* next;
} Mono;

int main() {
    Mono* ptr = (Mono*)malloc(sizeof(Mono));

    ptr[0].coef = 1;    /* array bracket style access */
    (*ptr).coef = 1;    /* dereference style access */
    ptr->coef = 1;      /* arrow style access */
}
