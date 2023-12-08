#include "dllist.h"
#include <stdio.h>

/* TODO (Q3.) Implement the incomplete functions below */

void initList(DLList* list)
{
   list->head = list->tail = NULL;
}

void clearList(DLList* list)
{
   /* TODO: 
   * Empty the list and free any allocated space 
   */
   if (list->head == NULL) {
      return;
   }
   DLNode* next = list->head->next;
   DLNode* curr = list->head;
   while (curr) {
      free(curr);
      if (!next) {
         break;
      }
      curr = next;
      next = next->next;
   }
   list->head = NULL;
   list->tail = NULL;
}

void insertFrontList(DLList* list,int v)
{
   DLNode* nn = malloc(sizeof(DLNode));
   nn->value = v;
   nn->next = nn->prv = NULL;
   if (list->head == NULL)
      list->head = list->tail = nn;
   else {
      nn->next = list->head;
      list->head->prv = nn;
      list->head = nn;
   }
}

void insertBackList(DLList* list,int v)
{
   DLNode* nn = malloc(sizeof(DLNode));
   nn->value = v;
   nn->next = nn->prv = NULL;
   if (list->head == NULL)
      list->head = list->tail = nn;
   else {
      list->tail->next = nn;
      nn->prv = list->tail;
      list->tail = nn;
   }
}

void insertInListBehind(DLList* list,int key,int v)
{
   /* TODO: insert an element right after a given element key 
   * If the key does not appear in the list, add the new element at the end.
   */
   DLNode* newnode = malloc(sizeof(DLNode));
   newnode->prv = NULL;
   newnode->next = NULL;
   newnode->value = v;
   if (list->head == NULL) {
      list->head = newnode;
      list->tail = newnode;
      return;
   }
   DLNode* traverse = list->head;
   while (traverse) {
      if (traverse->value == key) {
         if (traverse->next) {
            traverse->next->prv = newnode;
            newnode->next = traverse->next;
         }
         else {
            //traverse is the tail
            list->tail = newnode;
         }
         newnode->prv = traverse;
         traverse->next = newnode;
         return;
      }
      traverse = traverse->next;
   }
   // cannot find key, add at the end
   list->tail->next = newnode;
   newnode->prv = list->tail;
   list->tail = newnode;
}

void removeFromList(DLList* list,int key)
{
   if (!list->head) return;
   DLNode* curr = list->head;
   while (curr) {
      if (curr->value == key) {
         if (curr->prv) {
            curr->prv->next = curr->next;
         }
         if (curr->next) {
            curr->next->prv = curr->prv;
         }
         if (curr == list->head && curr == list->tail) {
            list->head = list->tail = NULL;
         }
         else if (curr == list->head) {
            list->head = curr->next;
         }
         else if (curr == list->tail) {
            list->tail = curr->prv;
         }
         free(curr);
         return;
      }
      curr = curr->next;
   }
}

void printListForward(DLList* list)
{
   DLNode* cur = list->head;
   while (cur) {
      printf("%d ",cur->value);
      cur = cur->next;
   }
   printf("\n");
}

void printListBackward(DLList* list)
{
   DLNode* cur = list->tail;
   while (cur) {
      printf("%d ", cur->value);
      cur = cur->prv;
   }
   printf("\n");
}
