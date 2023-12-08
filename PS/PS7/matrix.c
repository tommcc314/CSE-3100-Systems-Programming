#include "matrix.h"
#include <unistd.h>
#include <ctype.h>

size_t sizeMatrix(int r,int c)
{
   /* TODO:
    * Return the number of bytes needed to hold a matrix of r x c values (type int)
    */
   return sizeof(Matrix) + r * c * sizeof(int);
}

Matrix* makeMatrix(int r,int c)
{
   /* TODO:
    * Allocate space to hold a matrix of r x c values (type int)
    * Initialize the number of rows to r and number of columns to c
    */
   Matrix* newMatrix = malloc(sizeMatrix(r, c));
   newMatrix->r = r, newMatrix->c = c;
   return newMatrix;
}

Matrix* makeMatrixMap(void* zone,int r,int c)
{
   /* TODO:
    * Store a matrix of size r x c at the address 'zone'. 
    * Note: you do not need to use memory allocation here. Only point a matrix of size r and c to the memory zone.
    */
   Matrix* newMatrix = (Matrix*)zone;
   newMatrix->r = r, newMatrix->c = c;
   return newMatrix;
}

int readValue(FILE* fd)
{
   /* 
    * Reads a single integer from the FILE fd
    * Note: the function uses getc_unlocked to _not_ pay the overhead of locking and
    * unlocking the file for each integer to be read (imagine reading a matrix of 1000x1000,
    * that's 1,000,000 calls to getc and therefore 1,000,000 calls to locking the file. 
    */
   int v = 0;
   char ch;
   int neg=1;
   while (((ch = getc_unlocked(fd)) != EOF) && isspace(ch)); // skip WS.      
   while (!isspace(ch)) {
      if (ch=='-')
         neg=-1;
      else
         v = v * 10 + ch - '0';
      ch = getc_unlocked(fd);
   }
   return neg * v;
}

Matrix* readMatrix(FILE* fd)
{
   /*
    * Reads a matrix from a file (fd). The matrix is held in a text format that first conveys
    * the number of rows and columns, then, each row is on a line of text and all the 
    * values are separated by white spaces. 
    * Namely:
    * r c
    * v0,0 v0,1 .... v0,c-1
    * v1,0 v1,1 .... v1,c-1
    * ....
    * vr-1,0 ....    v_r-1,c-1
    */
   int r,c,v;
   int nv = fscanf(fd,"%d %d",&r,&c);
   Matrix* m = makeMatrix(r,c);
   flockfile(fd);
   for(int i=0;i < r;i++)
      for(int j=0;j < c;j++) {
         v = readValue(fd);
         M(m,i,j) = v;
      }
   funlockfile(fd);
   return m;
}


void freeMatrix(Matrix* m)
{
   /* TODO:
    * Deallocate the space used by matrix m
    */
   free(m);
}

void printMatrix(Matrix* m)
{
   /* TODO:
    * Print the matrix on the standard output. 
    * Print one row per line, values for the row separated by white spaces. 
    */
   for (int i = 0; i < m->r; ++i) {
      for (int j = 0; j < m->c; ++j) {
         printf("%3d ", M(m, i, j));
      }
      printf("\n");
   }
}

Matrix* multMatrix(Matrix* a,Matrix* b,Matrix* into)
{  
   /* TODO:
    * Compute the product of A * B and store the result in `into`.
    * * The computation here is sequential (done by 1 process) and is only meant to be used as a check for your parallel code. 
    * A matrix multiplication of size m x n * n x p yields an m x p matrix.
    *
    * Return the matrix `into` that stores the result.
    */
   for (int i = 0; i < a->r; ++i) {
      for (int j = 0; j < b->c; ++j) {
         for (int k = 0; k < a->c; ++k) {
            M(into, i, j) += M(a, i, k) * M(b, k, j);
         }
      }
   }
   return into;
}

Matrix* parMultMatrix(int nbW,sem_t* sem,Matrix* a,Matrix* b,Matrix* into)
{
   /* TODO:
    * Compute the product of A * B and store the result in `into`
    * The computation is done in parallel with nbW worker processes that you fork from here.
    * It should have the same output as the sequential version, but faster. ;-)
    * How you use the semaphore is up to you (as long as you use it!)
    * You CANNOT use the wait system call. 
    *
    * Return the matrix `into` that stores the result.
    */
   int baseline = a->r / nbW, startRow = 0, leftover = a->r % nbW, currWRows;
   for (int w = 0; w < nbW; ++w, startRow += currWRows, --leftover) {
      currWRows = baseline + (leftover > 0);
      pid_t worker = fork();
      if (worker == 0) {
         for (int i = startRow; i < startRow + currWRows; ++i) {
            for (int j = 0; j < b->c; ++j) {
               for (int k = 0; k < a->c; ++k) {
                  M(into, i, j) += M(a, i, k) * M(b, k, j);
               }
            }
         }
         sem_post(sem);
         exit(0);
      }
   }
   return into;
}
