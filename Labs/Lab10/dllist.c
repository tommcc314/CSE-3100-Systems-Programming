#include "dllist.h"
#include <stdio.h>
#include <assert.h>

void initList(DLList* list)
{
   list->head = list->tail = NULL;
   pthread_mutex_init(&list->mtx,NULL);
}

void clearList(DLList* list)
{
   pthread_mutex_lock(&list->mtx);
   DLNode* cur = list->head;
   while (cur) {
      DLNode* next = cur->next;
      pthread_mutex_destroy(&cur->mtx);
      free(cur);
      cur = next;
   }
   list->head = list->tail = NULL;
   pthread_mutex_unlock(&list->mtx);
}

void destroyList(DLList* list)
{
   clearList(list);
   pthread_mutex_destroy(&list->mtx);
}

void insertSortedList(DLList* list,int v)
{
  /*
    TODO: Iterate through the list, find the correct place to insert the integer v. Each node has a mutex; use those mutexes to coordinate the threads. 
    Note: Your code will be checked manually to ensure that fine-grained locking is used. If you use coarse-grained locking to pass the tests, no points will be awarded.
   */
   //create node
   DLNode* node = (DLNode*)malloc(sizeof(DLNode));
   node->value = v;
   pthread_mutex_init(&node->mtx, NULL);
   DLNode* cur = list->head;
   DLNode* prev = NULL;
   // while iterating, lock the cur and prev nodes if they exist so that the actions of other threads do not cause issues.
   if (cur) pthread_mutex_lock(&cur->mtx);
   while (cur) {
      if (cur->value < v) {
         // unlock the prev and then lock the next
         if (prev) pthread_mutex_unlock(&prev->mtx);
         prev = cur;
         cur = cur->next;
         if (cur) pthread_mutex_lock(&cur->mtx);
      }
      else {
         break;
      }
   }
   // now the cur and prev are still locked if they exist
   node->next = cur;
   if (prev) {
      prev->next = node;
      pthread_mutex_unlock(&prev->mtx);
   } else {
      pthread_mutex_lock(&list->mtx);
      list->head = node;
      pthread_mutex_unlock(&list->mtx);
   }
   if (cur) {
      cur->prv = node;
      pthread_mutex_unlock(&cur->mtx);
   } else {
      pthread_mutex_lock(&list->mtx);
      list->tail = node;
      pthread_mutex_unlock(&list->mtx);
   }
}

void printListForward(DLList* list)
{
   pthread_mutex_lock(&list->mtx);
   DLNode* cur = list->head;
   pthread_mutex_t* last = &list->mtx;
   while (cur) {
      pthread_mutex_lock(&cur->mtx);
      printf("%d ",cur->value);
      pthread_mutex_unlock(last);
      last = &cur->mtx;
      cur = cur->next;
   }
   printf("\n");
   pthread_mutex_unlock(last);
}
