#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define READEND     0
#define WRITEEND    1

/* This function computes prefix sum for indices start to end and stores it in result */
void computePrefixSum(int *arr, int start, int end, int *result) 
{
    result[start] = arr[start];
    for (int i = start + 1; i <= end; ++i) {
        result[i] = result[i - 1] + arr[i];
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./pipe-prefixsum n \n");
        return -1;
    }

    int n = atoi(argv[1]);      /* Number of elements */

    /* Read the numbers from the user and store them in arr */
    printf("Please input %d integers\n", n);
    int arr[n];
    for(int i=0; i<n; i++) {
        scanf("%d", arr+i);
    }

    /* Print the original array */
    printf("Original Array:");
    for (int i = 0; i < n; ++i) {
        printf(" %d", arr[i]);
    }
    printf("\n");

    /* Create arrays to store prefix sums */
    int prefixSum[n];           /* used by child processes to compute and store prefixes */
    int half = n / 2;
    int childPrefixSum1[half];  /* used by parent processes to temporarily store prefixes sent by child 1 */
    int childPrefixSum2[half];  /* used by parent processes to temporarily store prefixes sent by child 2 */
   
    /* TODO (Q1.) 
     * Set up pipes and child processes to compute prefix sum.
     * Child 1 calls computePrefixSum() to compute the prefix sum of first half of arr, stores it in prefixSum and sends it to the parent.
     * Child 2 calls computePrefixSum() to compute the prefix sum of second half of arr, stores it in prefixSum and sends it to the parent.
     * Parent: Reads the prefixSum from both child processes, stores them in childPrefixSum1 and childPrefixSum2, and combines the result in prefixSum.
        * The code to combine and print the arrays is given below.
        * The parent must wait for the child processes to terminate.
        
     * Note: All processes should close file descriptors that are not needed.
     * If any of read(), write(), or fork() fails, exit from the process with a value of -1.
    */
    int p1[2], p2[2];
    pipe(p1), pipe(p2);
    pid_t child1 = fork();
    if (child1 == 0) {
        // compute first half
        close(p2[READEND]);
        close(p2[WRITEEND]);
        close(p1[READEND]);
        computePrefixSum(arr, 0, half - 1, prefixSum);
        int writeres = write(p1[WRITEEND], prefixSum, sizeof(prefixSum));
        if (writeres == -1) {
            printf("Something went wrong while writing: %s\n", strerror(errno));
            exit(-1);
        }
        return 0;
    }
    else if (child1 == -1){
        // check error
        printf("Something went wrong while forking: %s\n", strerror(errno));
        exit(-1);
    }
    else {
        pid_t child2 = fork();
        if (child2 == 0) {
            //compute second half
            close(p2[READEND]);
            close(p1[WRITEEND]);
            close(p1[READEND]);
            computePrefixSum(arr, half, n - 1, prefixSum);
            int writeres = write(p2[WRITEEND], &prefixSum[half], sizeof(prefixSum) / 2);
            if (writeres == -1) {
                printf("Something went wrong while writing: %s\n", strerror(errno));
                exit(-1);
            }
            return 0;
        }
        else if (child2 == -1) {
            // check error
            printf("Something went wrong while forking: %s\n", strerror(errno));
            exit(1);
        }
        else {
            //parent
            close(p1[WRITEEND]);
            close(p2[WRITEEND]);
            int readres1 = read(p1[READEND], childPrefixSum1, sizeof(childPrefixSum1));
            int readres2 = read(p2[READEND], childPrefixSum2, sizeof(childPrefixSum2));
            if (readres1 == -1 || readres2 == -1) {
                printf("Something went wrong while reading: %s\n", strerror(errno));
                exit(-1);
            }
            // wait on the 2 children
            int exitStatus;
            pid_t deadChild = wait(&exitStatus);
            deadChild = wait(&exitStatus);
        }
    }

   

    /* Combining the results */
    for (int i = 0; i < half; ++i)
        prefixSum[i] = childPrefixSum1[i];
    for (int i = 0; i < half; ++i)
        prefixSum[i+half] = childPrefixSum2[i] + prefixSum[half-1];

    /* Print the results */
    printf("Prefix Sum Array:");
    for (int i = 0; i < n; ++i)
        printf(" %d", prefixSum[i]);
    printf("\n");

    return 0;
}