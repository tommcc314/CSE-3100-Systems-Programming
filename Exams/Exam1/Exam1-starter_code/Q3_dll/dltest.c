#include "dllist.h"
#include <stdio.h>
#include <string.h>
/* DO NOT EDIT THIS PROGRAM */

int main()
{
   char com[16];
   DLList* lst = malloc(sizeof(DLList));
   initList(lst);
   while(scanf("%s",com) == 1) {
      if (strncmp(com,"fr",2) == 0) {
         int v = 0;
         scanf("%d",&v);
         insertFrontList(lst,v);
      } else if (strncmp(com,"bk",2) == 0) {
         int v = 0;
         scanf("%d",&v);
         insertBackList(lst,v);
      } else if (strncmp(com,"in",2) == 0) {
         int key=0,v = 0;
         scanf("%d %d",&key,&v);
         insertInListBehind(lst,key,v);         
      } else if (strncmp(com,"rl",2) == 0) {
         int v = 0;
         scanf("%d",&v);
         removeFromList(lst,v);
      } else if (strncmp(com,"pf",2) == 0) {
         printListForward(lst);
      } else if (strncmp(com,"pb",2) == 0) {
         printListBackward(lst);
      } else if (strncmp(com,"cl",2) == 0) {
         clearList(lst);
      }
   }
   clearList(lst);
   free(lst);
   return 0;
}
