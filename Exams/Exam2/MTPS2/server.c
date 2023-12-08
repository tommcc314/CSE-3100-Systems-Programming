#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <errno.h>

#define BUFFER_SIZE 1024

void handleClient(int clientSocket);

int checkError(int status) {
   if (status < 0) {
      printf("socket error(%d): [%s]\n",getpid(),strerror(errno));
      return 1;
   }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return -1;
    }

    int status;

    /* Create a server socket */
    int sid = socket(PF_INET, SOCK_STREAM, 0);

    /* Set up server address and bind to the socket */
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[1]));
    addr.sin_addr.s_addr = INADDR_ANY;
    status = bind(sid, (struct sockaddr *)&addr, sizeof(addr));
    checkError(status);

    /* Listen on that socket for let's connect message. No more than 1 pending at once. */
    status = listen(sid, 1);
    checkError(status);

    printf("Server is listening on port %s\n", argv[1]);

    fd_set readfds;
    int clientSocket = -1;
    int maxSocket;

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(sid, &readfds);
        maxSocket = sid;

        if (clientSocket != -1) {
            FD_SET(clientSocket, &readfds);
            if (clientSocket > maxSocket) {
                maxSocket = clientSocket;
            }
        }
        
        // Use select to monitor sockets for activity
        int nbReady = select(maxSocket + 1, &readfds, NULL, NULL, NULL);
        if(nbReady > 0) {
            // Check for incoming connection
            if (FD_ISSET(sid, &readfds)) {
                if (clientSocket == -1) {
                    struct sockaddr_in client;
                    socklen_t clientSize = sizeof(client);
                    clientSocket = accept(sid, (struct sockaddr *)&client, &clientSize);
                    checkError(clientSocket);
                    printf("We accepted a socket: %d\n",clientSocket);
                } else {
                    printf("Connection refused. Already one client connected.\n");
                }
            }

            // Check for data from the client
            if (clientSocket != -1 && FD_ISSET(clientSocket, &readfds)) {
                handleClient(clientSocket);
            }
        }
    }

    // Close server socket (never reached in this example)
    close(sid);

    return 0;
}

void handleClient(int clientSocket) {
    char buffer[BUFFER_SIZE];

    /* Receive arithmetic expression from the client */
    int bytesRead = read(clientSocket, buffer, BUFFER_SIZE);
    buffer[bytesRead] = '\0';
    printf("Received from client: %s", buffer);

    if(strncmp(buffer, "quit", 4) == 0) {
        printf("Client disconnected.\n");
        close(clientSocket);
        exit(0);
        //return;
    }

    /* Evaluate the arithmetic expression */
    int num1, num2;
    char operator;
    sscanf(buffer, "%d %c %d", &num1, &operator, &num2);

    // Perform the calculation
    int result;
    switch (operator) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 != 0)
                result = num1 / num2;
            else
                result = -1; // Indicate division by zero
            break;
        default:
            result = -1; // Indicate invalid operator
    }

    /* Send the result back to the client */
    sprintf(buffer, "%d\n", result);
    write(clientSocket, buffer, strlen(buffer));
}
