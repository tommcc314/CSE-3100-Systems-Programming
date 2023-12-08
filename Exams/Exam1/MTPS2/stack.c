#include "stack.h"
#include <stdlib.h>

IStack* makeStack() {
   /* TODO
    * Allocate memory for a stack and initialize it.
    * Never allocate memory more than twice the size of the stack.
    */
    IStack* newstack = (IStack*)malloc(sizeof(IStack));
    newstack->mx = 1;
    newstack->sz = 0;
    newstack->t = (int*)malloc(sizeof(int));
    return newstack;
}

void freeStack(IStack* s) {
   /* TODO
    * Release all allocated memory. 
    */
    free(s->t);
    free(s);
    return;
}

void pushStack(IStack* s,int v) {
   /* TODO 
    * Push an element on the stack. If the stack has no space left, first allocate more space.
    * Never allocate memory more than twice the size of the stack.
   */
    s->sz++;
    if (s->sz > s->mx) {
        s->t = (int*)realloc(s->t, (s->sz * 2) * sizeof(int));
    }
    s->mx = s->sz * 2;
    s->t[s->sz - 1] = v;
}

int popStack(IStack* s) {
    /* TODO
    * Pop an element from the stack.
    */
    return s->t[--s->sz];
}

int isEmptyStack(IStack* s) {
    /* TODO
     * Return 1 if the stack is empty. Otherwise, return 0.
     */
    return s->sz == 0;
}
