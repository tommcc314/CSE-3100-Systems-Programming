#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define READEND 0
#define WRITEEND 1
int main(int argc,char* argv[])
{
   if (argc < 2) {
      printf("usage is: %s <filesystem>\n", argv[0]);
      exit(1);
   }

   /* TODO:
    * Take the name of a filesystem from the user in argv[1]
    * Implement the following pipeline command:
        * df -h | grep argv[1]
    */
    int p[2];
    pipe(p);
    pid_t child = fork();
    if (child == 0) {
        dup2(p[WRITEEND], STDOUT_FILENO);
        close(p[WRITEEND]);
        close(p[READEND]);
        execl("/usr/bin/df", "df", "-h", NULL);
    }
    else {
        dup2(p[READEND], STDIN_FILENO);
        close(p[WRITEEND]);
        close(p[READEND]);
        execl("/usr/bin/grep", "grep", argv[1], NULL);
    }
}


