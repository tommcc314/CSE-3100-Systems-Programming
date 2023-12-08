#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include "token.h"

/* TODO: complete the implementation of an RPN calculator */

int main() {
   /* The function read tokens from the stdin till the user inputs EOF or the quit command.
        * If the token is a literal, push the value on the stack.
        * If the token is an operator, pop values from the stack and perform the operation. Push the result on the stack.
        * If the token is 'p', pop and print a value from the stack.
        * If the token is 'q', stop reading the tokens.
     */

   Token tok;
   IStack* s = makeStack();
   int goOn  = 1;
   int x1, x2;
   while (goOn && readToken(&tok) != 0) {
      switch(tok.type) {
         /* TODO: complete the following operations as explained in the pdf and above */
         case LIT: 
            pushStack(s, tok.value);
            break;
         case '+': /* Fill this in. */
            x2 = popStack(s);
            x1 = popStack(s);
            pushStack(s, x1 + x2);
            break;
         case '*': /* Fill this in. */
            x2 = popStack(s);
            x1 = popStack(s);
            pushStack(s, x1 * x2);
            break;
         case '-': /* Fill this in. */
            x2 = popStack(s);
            x1 = popStack(s);
            pushStack(s, x1 - x2);
            break;
         case '/': /* Fill this in. */
            x2 = popStack(s);
            x1 = popStack(s); 
            pushStack(s, x1 / x2); 
            break;          
         case 'p': /* Fill this in. */
            printf("%d\n", popStack(s));
         case 'q': goOn = 0; break;
      }
   }
   freeStack(s);
   return 0;
}

