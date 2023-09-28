#include <stdio.h>
#include "queue.h"

void initQueue(Queue* q)
{
    /* TODO: Allocate memory and initialize the stacks of the queue. */
    q->one = malloc(sizeof(Stack));
    q->two = malloc(sizeof(Stack));
    initStack(q->one);
    initStack(q->two);
}

void enQueue(Queue* q, int number)
{
    /* TODO: Fill this in, one line of code */
    pushStack(q->one, number);
}

int deQueue(Queue* q)
{
  /*
    TODO: Check if stack 2 is empty. If it is, flip all of the elements from stack 1 to stack 2. Then, pop and return the element from stack 2.
   */
    if (isEmpty(q->two)) {
        int oneSize = q->one->list->len;
        for (int i = 0; i < oneSize; ++i) {
            pushStack(q->two, popStack(q->one));
        }
    }
    return popStack(q->two);
}

void freeQueue(Queue* q)
{
    /* TODO: Free up all the allocated memory. */
    freeStack(q->one);
    freeStack(q->two);
}
