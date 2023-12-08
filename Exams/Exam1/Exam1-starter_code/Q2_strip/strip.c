#include "strip.h"
#include <stdio.h>
#include <stdlib.h>
/* You cannot add more header files */
/* Any helper functions you need, you must implement */

char* strip(char* s)
{
   /* TODO (Q2.) 
    * In place trimming of s. Go to the end of the string and remove all spaces.
    * Note that you cannot make use of built-in string library functions. You will not earn any points if you do. 
    * You may, however, write your own string functions that you need.
    * Return a pointer to the trimmed string.
    */
    int len = 0;
    char* traverse = s;
    while (*traverse != 0) {
        len++;
        traverse++;
    }
    int i = len - 1;
    while (i >= 0 && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\r')) {
        --i;
    }
    s[i + 1] = 0;
    return s;
}


