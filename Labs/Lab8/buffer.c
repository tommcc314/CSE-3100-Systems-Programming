#include "buffer.h"
#include <sys/mman.h>
#include <sys/stat.h>        
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>

SBuffer* makeBuffer(void* z,int sz,size_t mapSize) {
   /* TODO
   * Initialize and return a shared buffer pointer that can be held at address z.
   * The buffer should have a capacity sz and size of mapSize.
   */
   SBuffer* newBuffer = (SBuffer*)z;
   newBuffer->sz = sz;
   newBuffer->mapSize = mapSize;
   newBuffer->nb = 0;
   newBuffer->enter = 0;
   newBuffer->leave = 0;
   return newBuffer;
}

void bufferEnQueue(SBuffer* b,Task t) {
   /* TODO: add Task t to the shared buffer b. 
   * Do not use synchronization here. */
   b->data[b->enter] = t;
   b->enter = (b->enter + 1) % b->sz;
   ++b->nb;
}

Task bufferDeQueue(SBuffer* b) {
   /* TODO: deQueue and return a task from the shared buffer b. 
   * Do not use synchronization here. */
   Task left = b->data[b->leave];
   b->leave = (b->leave + 1) % b->sz;
   --b->nb;
   return left;
}

SBuffer* setupBuffer(char* zone,int nbTasks) {
   /* TODO: 
    * Create a memory mapping of the shared object "zone" capable of holding SBuffer and nbTasks entries.
    * Initialize the SBuffer and return the address of the shared buffer. 
    */
   int md = shm_open(zone, O_RDWR|O_CREAT, S_IRWXU); //create a shared memory object
   int size = sizeof(SBuffer) + nbTasks * sizeof(Task);
	ftruncate(md, size); 

	SBuffer *newBuffer = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, md, 0); //map the object to the memory
   newBuffer = makeBuffer(newBuffer, nbTasks, size);
   return newBuffer;
}

SBuffer* getBuffer(char* zone,int nbTasks) {
   /* TODO: Given a shared memory object "zone", retrieve it and return the address of the mapping. */ 
   int md = shm_open(zone, O_RDWR, S_IRWXU); //create a shared memory object
   int size = sizeof(SBuffer) + nbTasks * sizeof(Task);
   SBuffer* buffer = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_FILE, md, 0); //map the object to the memory
   return buffer;
}

void tearDownBuffer(char* zone,SBuffer* b) {
   /* TODO: Release the resources (map/shared object) needed for the shared buffer b */
   int md = shm_open(zone, O_RDWR, S_IRWXU);
   munmap(b, sizeof(b));
	close(md); //close the file descriptor
   shm_unlink(zone);
}
