#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void initList(IntList* list)
{
    /*
        TODO: The IntList structure is already allocated in memory. You need to fill the fields in. 
    */
    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
}

void freeList(IntList* list)
{
  /*
    TODO: You need to free each node in the list. However, the actual list itself doesn't need to be freed here.
   */
    ILNode *curr = list->head;
    ILNode *next = list->head;
    while (curr) {
        next = curr->next;
        free(curr);
        curr = next;
    }
    list->len = 0;
    list->head = NULL;
    list->tail = NULL;
}

void pushBackList(IntList* list, int number)
{
    /*
        TODO: Add a node containing the number to the end of the list
    */
    ILNode* newNode = (ILNode*)malloc(sizeof(ILNode));
    if (list->tail)
        list->tail->next = newNode;
    list->tail = newNode;
    if (!list->head)
        list->head = newNode;
    newNode->number = number;
    list->len++;
}

int popBackList(IntList* list)
{
    assert(list->head && list->tail && list->len > 0);
        /*
        TODO: Remove the tail node of the list, and return the integer contained in it.
    */
    ILNode* toRemove = list->tail;
    int val = toRemove->number;
    if (list->head == toRemove) {
        list->head = NULL;
        list->tail = NULL;
    }
    else {
        ILNode* findTail = list->head;
        while (findTail->next != toRemove) {
            findTail = findTail->next;
        }
        list->tail = findTail;
        findTail->next = NULL;
    }
    list->len--;
    free(toRemove);
    return val;
}

void pushFrontList(IntList* list, int number)
{
    /*
        TODO: Add a node containing the number to the start of the list 
    */
    ILNode* newNode = (ILNode*)malloc(sizeof(ILNode));
    newNode->next = list->head;
    list->head = newNode;
    if (!list->tail)
        list->tail = newNode;
    newNode->number = number;
    list->len++;
}

int popFrontList(IntList* list)
{
    assert(list->head && list->tail && list->len > 0);
    /*
        TODO: Remove the head node of the list, and return the integer contained in it. 
    */
    ILNode* toRemove = list->head;
    int val = toRemove->number;
    if (list->tail == toRemove)
        list->tail = NULL;
    list->head = list->head->next;
    list->len--;
    free(toRemove);
    return val;
}

void sortedInsert(IntList* sortedList, ILNode* nodeToInsert){
    /*
        TODO: You're given a linked list where the nodes are sorted (the smallest number is at the head, the largest at the tail). Iterate through the list until you find where to insert nodeToInsert, so as to keep the list sorted, and insert it. 
    */
    if (sortedList->head == NULL)
  {
    sortedList->head = nodeToInsert;
    sortedList->tail = nodeToInsert;
    nodeToInsert->next = NULL;
  }
  else
  {
    ILNode *node = sortedList->head;
    ILNode *prev = NULL;
    while (node && node->number < nodeToInsert->number)
    {
      prev = node;
      node = node->next;
    }
    if (prev)
    {
      prev->next = nodeToInsert;
    }
    else
    {
      sortedList->head = nodeToInsert;
    }
    nodeToInsert->next = node;
    if (node == NULL)
    {
      sortedList->tail = nodeToInsert;
      nodeToInsert->next = NULL;
    }
  }
  sortedList->len++;
}

void sortList(IntList* list)
{
  IntList newList = {NULL,NULL};
  ILNode* next = NULL;
  ILNode* cur = list->head;
  while(cur){
    next = cur->next;
    sortedInsert(&newList, cur);
    cur = next;
  }
  *list = newList;
}

int lengthList(IntList* list)
{
  return list->len;
}

void printList(IntList* list)
{
   printf("(");
   ILNode* node = list->head;
   while (node) {
      printf("%d ", node->number);
      node = node->next;
   }
   printf(")\n");
}
