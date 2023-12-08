/* Multiple calls to fork() */

#include <stdio.h> 
#include <unistd.h>

int main() {
     pid_t value;
     value = fork(); 
     value = fork();
     value = fork();
     printf("In main of pid %d, the value = %d\n", getpid(), value);

     return 0;
}