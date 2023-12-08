/* NOTE: To test this program, you must create a copy of vector.c and vector.h that you've implemented in 1.2 */

#include "VStack.h"

void initStack(Stack * s)
{
    /* TODO: Fill this in. One line of code. */
    s->vector = malloc(sizeof(IntVector));
    initVector(s->vector, 1);

}

void pushStack(Stack* stack, int number)
{
  /* TODO: Fill this in. One line of code. */
  pushBackVector(stack->vector, number);
}

int popStack(Stack* stack)
{
  /* TODO: Fill this in. One line of code. */
  return popBackVector(stack->vector);
}

void freeStack(Stack* stack)
{
  /* TODO: Fill this in. One line of code. */
  freeVector(stack->vector);
}

void printStack(Stack* stack)
{
  /* TODO: Fill this in. One line of code. */
  printVector(stack->vector);
}

int isEmpty(Stack* stack)
{
  /* TODO: Fill this in. One line of code. */
  return stack->vector->size == 0;
}
