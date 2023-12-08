#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include "guess-mt.h"

typedef struct thread_arg_tag {
    gmn_t* sb;
    /* TODO 
     * Add mutexes and condition variables required
    */
    pthread_mutex_t mtx;
    pthread_cond_t guessWaiting;
    pthread_cond_t resultWaiting;
} thread_arg_t;

void *thread_c(void* consumer_thread_data);
void *thread_p(void* producer_thread_data);

int main(int argc,char* argv[])
{
    int status;
    thread_arg_t comm;
    comm.sb = gmn_init(atoi(argv[1]));
    pthread_t parent, child;
    /* TODO
     * Create an instance of thread_arg_t and initialize it. The value to be guessed is taken as input from the command line arguments.
     * Create two threads - one each for the parent and child
     * Join the threads and reap the resources (destroy the mutexes and condition variables used).
    */
    pthread_mutex_init(&comm.mtx, NULL);
    pthread_cond_init(&comm.guessWaiting, NULL);
    pthread_cond_init(&comm.resultWaiting, NULL);
    status = pthread_create(&parent, NULL, (void *(*)(void *))thread_p, (void *) &comm);
    status = pthread_create(&child, NULL, (void *(*)(void *))thread_c, (void *) &comm);
    void* p, *c;
    pthread_join(parent, &p), pthread_join(child, &c);
    pthread_mutex_destroy(&comm.mtx);
    pthread_cond_destroy(&comm.guessWaiting), pthread_cond_destroy(&comm.resultWaiting);
    free(comm.sb);
    return 0;
}

void* thread_p(void *producer_thread_data) {
   /* TODO
    * This is a parent thread.
    * repeat the following until guess is correct
        guess a number between min and max. initially max is set to MAX_VALUE
        send the guess to the child and wait for a result (thread_c)
        if result is 0 i.e. you guessed the number correctly, end the thread
        if result is -1 or 1, update the search interval and make a guess
   */
    thread_arg_t* comm = producer_thread_data;
    int max = MAX_VALUE, min = 1;
    while (1) { 
        pthread_mutex_lock(&comm->mtx);
        comm->sb->guess = (max + min) / 2;
        sprintf(comm->sb->message, "My guess is %d.\n\n", comm->sb->guess);
        printf("%s", comm->sb->message);
        comm->sb->status = 1;
        pthread_cond_signal(&comm->guessWaiting);
        while (comm->sb->status) {
            pthread_cond_wait(&comm->resultWaiting, &comm->mtx);
        }
        if (comm->sb->result == 0) break;
        else if (comm->sb->result < 0) max = comm->sb->guess - 1;
        else min = comm->sb->guess + 1;
        printf("%s\n", comm->sb->message);
        pthread_mutex_unlock(&comm->mtx);
    }
    return NULL;
}

void* thread_c(void * consumer_thread_data)
{
    /* TODO
     * This is a child thread.
     * repeat the following until guess is correct 
     *      wait for a guess from the parent (thread_p) 
     *      call gmn_check() to compare the guess with the user input value
     *      send the result to thread_p
     */
    thread_arg_t* comm = consumer_thread_data;
    while (1) {
        pthread_mutex_lock(&comm->mtx);
        while (!comm->sb->status) {
            pthread_cond_wait(&comm->guessWaiting, &comm->mtx);
        }
        int res = gmn_check(comm->sb);
        comm->sb->result = res;
        comm->sb->status = 0;
        pthread_cond_signal(&comm->resultWaiting);
        pthread_mutex_unlock(&comm->mtx);
        if (!res) break;
    }
    return NULL;
}
