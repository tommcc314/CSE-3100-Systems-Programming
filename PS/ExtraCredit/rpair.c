#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <string.h>
#include <errno.h>
#include <math.h>

/* TODO: Complete the main and createSamples functions */

long createSamples(unsigned wID,long nbSamples,double d)
{
   long ttl = 0; // Number of events detected by a process
   unsigned seed = wID; //seed for random number generation

   /* TODO
    * This function is called by all processes to perform nbSamples number of trials
    * wID is the int id of a worker process that ranges from 0 to nbW-1 and is used as a seed value for random number generation.
    * You may use rand_r() from stdlib.h to generate random numbers between 0 and RAND_MAX. The usage of rand_r() can be found in the manual page: man -S2 rand.
    * The random numbers can be normalized to an interval [0, 1) by dividing them by RAND_MAX. 
    * The function returns the number of events occurred in nbSamples trials.
    */

   for (int i = 0; i < nbSamples; ++i) {
      double x = (double) rand_r(&seed) / RAND_MAX, y = (double) rand_r(&seed) / RAND_MAX;
      if ((x < y ? y - x : x - y) < d) ++ttl;
   }
   return ttl;
}

int main(int argc,char* argv[])
{
   if (argc < 4) {
      printf("usage: rpair <d> <samples> <workers>\n");
      exit(1);
   }
   float d = atof(argv[1]); // value of d
   long s  = atol(argv[2]); // total number of trials to be executed
   int nbW = atoi(argv[3]); // number of worker processes

   long ttl = 0; //total number of events
   double p = 0; //Probability of the occurence of events
   const char* zone = "/memzone1";
	int md = shm_open(zone, O_RDWR|O_CREAT, S_IRWXU); //create a shared memory object
	int status = ftruncate(md, 4096); //size of the object is exactly 1 page

	long *t = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, md, 0); //map the object to the memory
	if(t == MAP_FAILED) {
		printf("mmap failure: %s\n", strerror(errno));
		exit(1);
	}

	memset(t,0,4096); //initialize the contents of the page to 0

	// Create a semaphore
	sem_t* sema = sem_open("/sema", O_CREAT, 0666, 1); //read write permissions are given; initialized to high
   /* TODO
    * This is the parent process that sets up the computation involving shared maps and multiple processes.
    * The computation must be fairly distributed among nbW worker (child) processes.
    * The parent must aggregate the results from all worker processes, report the final result, release all resources.
    */
   long leftover = s % nbW, base = s / nbW;
   for (int i = 0; i < nbW; ++i) {
      pid_t child = fork();
      if (child == 0) {
         long events = createSamples(i, base + (i < leftover), d);
         sem_wait(sema);
         t[0] += events;
         sem_post(sema);
         return 0;
      }
   }
   for (int i = 0, exitStatus; i < nbW; ++i) {
      pid_t deadChild = wait(&exitStatus);
   }
   sem_wait(sema);
   ttl = t[0];
   sem_post(sema);
   p = (double) ttl / s;
   printf("Total trials = %ld \t Total events = %ld \t Probability = %lf\n",s,ttl,p);
   munmap(t, 4096);
	close(md); //close the file descriptor
	shm_unlink(zone);
	sem_close(sema);
   return 0;
}
