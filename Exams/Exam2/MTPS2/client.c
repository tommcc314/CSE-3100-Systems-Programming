#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/select.h>
#include <assert.h>

#define BUFFER_SIZE 1024

void checkError(int status,int line)
{
   if (status < 0) {
      printf("socket error(%d)-%d: [%s]\n",getpid(),line,strerror(errno));
      exit(-1);
   }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <hostname> <port>\n", argv[0]);
        return 1;
    }

    int clientSocket;
    char buffer[BUFFER_SIZE];

    /* Create client socket */
    clientSocket = socket(PF_INET, SOCK_STREAM, 0);

    /* Set up server address and send a connect request */
    struct sockaddr_in srv;
    struct hostent *server = gethostbyname(argv[1]);
    if (server==NULL) {
      printf("Couldn't find a host named: %s\n",argv[1]);
      return 2;
    }
    srv.sin_family = AF_INET;
    srv.sin_port   = htons(atoi(argv[2]));
    memcpy(&srv.sin_addr,server->h_addr_list[0],server->h_length);
    int status = connect(clientSocket,(struct sockaddr*)&srv,sizeof(srv));
    checkError(status,__LINE__);

    printf("Connected to Calculator Server.\n");

    // File descriptors for select
    fd_set readSet;

    while (1) {
        FD_ZERO(&readSet);
        FD_SET(STDIN_FILENO, &readSet);
        FD_SET(clientSocket, &readSet);

        int nbReady = select(clientSocket + 1, &readSet, NULL, NULL, NULL);
        if(nbReady > 0) {
            // Check for user input from stdin
            if (FD_ISSET(STDIN_FILENO, &readSet)) {
                // Get user input for arithmetic expression
                printf("Expression entered: ");
                fgets(buffer, BUFFER_SIZE, stdin);

                // Send expression to server
                write(clientSocket, buffer, strlen(buffer));
                if(strncmp(buffer, "quit", 4)==0) {
                    close(clientSocket);
                    exit(0);
                }
            }

            // Check for data from server
            if (FD_ISSET(clientSocket, &readSet)) {
                int bytesRead = read(clientSocket, buffer, BUFFER_SIZE);
                if (bytesRead <= 0) {
                    printf("Server disconnected.\n");
                    close(clientSocket);
                    clientSocket = -1;
                    break;
                } else {
                    buffer[bytesRead] = '\0';
                    printf("Server Response: %s\n", buffer);
                }
            }
        }
    }

    return 0;
}
