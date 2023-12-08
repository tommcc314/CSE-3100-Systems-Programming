/* NOTE: To test this program, you must create a copy of list.c and list.h that you've implemented in 1.1 */

#include "LStack.h"

void initStack(Stack *s)
{
    /* TODO: Fill this in. One line of code. */
    s->list = malloc(sizeof(IntList));
    initList(s->list);
}

void pushStack(Stack* stack, int number)
{
    /* TODO: Fill this in. One line of code. */
    pushBackList(stack->list, number);
}

int popStack(Stack* stack)
{
    /* TODO: Fill this in. One line of code. */
    return popBackList(stack->list);
}

void freeStack(Stack* stack)
{
    /* TODO: Fill this in. One line of code. */
    freeList(stack->list);
}  

void printStack(Stack* stack)
{
    /* TODO: Fill this in. One line of code. */
    printList(stack->list);
}

int isEmpty(Stack* stack)
{
    /* TODO: Fill this in. One line of code. */
    return stack->list->len == 0;
}
