#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void initVector(IntVector* vec, int cap)
{
    /*
        TODO: The IntVector structure is already allocated in memory. You need to fill in the fields of it. For this, you'll need to allocate an array for cap integers.
    */
    vec->capacity = cap;
    vec->numbers = (int*)malloc(cap * sizeof(int));
    vec->size = 0;
}

void freeVector(IntVector* vec)
{
    /*
        TODO: Free the integer array that the IntVector contains. 
    */
    vec->size = 0;
    vec->capacity = 0;
    free(vec->numbers);
}

void expandVector(IntVector* vec)
{
    vec->capacity *= 2;
    /*
        TODO: Use the realloc function to double the capacity of the vector. This is only one line. 
    */
    vec->numbers = realloc(vec->numbers, vec->capacity * sizeof(int));
}
void pushBackVector(IntVector* vec, int number)
{
    /*
        TODO: First, check if the vector size is equal to capacity. If it is, then expand it. Then, make the last element of the vector be number; don't forget to increase the size field.
    */
    if (vec->size == vec->capacity)
        expandVector(vec);
    vec->numbers[vec->size++] = number;
}

int popBackVector(IntVector* vec)
{
    assert(vec->size > 0); /* asserts that the vector contains at least 1 element */
    /* 
        TODO: Remove and return the last element. Decrease the vector size by 1. 
    */
    vec->size--;
    return vec->numbers[vec->size];
}

void pushFrontVector(IntVector* vec, int number)
{
    /*
        TODO: First, check if the vector size is equal to the capacity. If it is, then expand it. Then, insert an element into the front of the vector. Don't forget to increment the size. 
    */
    if (vec->size == vec->capacity)
        expandVector(vec);
    for (int i = vec->size; i > 0; --i)
        vec->numbers[i] = vec->numbers[i - 1];
    vec->numbers[0] = number;
    vec->size++;
}

int popFrontVector(IntVector* vec)
{
    assert(vec->size > 0);
    /*
        TODO: Remove and return the number at the head of the vector. Be sure to shift remaining elements over to the left (toward the start of the vector) by one place. 
    */
    int val = vec->numbers[0];
    for (int i = 0; i < vec->size; ++i)
        vec->numbers[i - 1] = vec->numbers[i];
    vec->size--;
    return val;
}

void swap(IntVector* vec, size_t indexOne, size_t indexTwo)
{
    assert(indexOne < vec->size);
    assert(indexTwo < vec->size);
    int temp = vec->numbers[indexOne];
    vec->numbers[indexOne] = vec->numbers[indexTwo];
    vec->numbers[indexTwo] = temp;
}

void sortVector(IntVector* vec)
{
    /*
        TODO: Implement Insertion Sort to sort the vector. The swap function will be useful here. 
    */
    for (int i = 0; i < vec->size; ++i) {
        for (int j = i + 1; j < vec->size; ++j) {
            if (vec->numbers[j] < vec->numbers[i])
                swap(vec, i, j);
        }
    }
}

void printVector(IntVector* vec)
{
  printf("(");
  for(size_t i = 0; i < vec->size; i++){
    printf("%d ", vec->numbers[i]);
  }
  printf(")\n");
}

int lengthVector(IntVector* vec)
{
  return vec->size;
}
