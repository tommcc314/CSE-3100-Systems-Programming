/* Using bitfields: to optimize storage inside structures 
 * To store: age (1-128), gender (M/F/N) and species (can be given numeric encoding)
*/

#include <stdio.h>

typedef struct Census {
    int age;
    int gender;
    int species;
} Census; // Takes up to 16 bytes of storage (including padding)

/* Using bitfield, we require the following storage 
 * age (0-128): 7 bits
 * gender: 2 bits
 * species: 3 bits to store 8 species
 * Total: 12 bits or 2 bytes. That's 83% smaller!
*/

typedef struct Census2 {
    short age : 7; //using first 7 bits from a short (a short is 2 bytes)
    short gender: 2; //using the next 2 bits to store a gender
    short species: 3; //using the next 3 bits to store species
} Census2;

int main() {
    Census2 pop;
    pop.age = 2;
    pop.gender = 1;
    pop.species = 0;
    printf("The species is a %d and has age = %d and gender = %d\n", pop.species, pop.age, pop.gender);
    return 0;
}