#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>

#define MAX_BUFFER_SIZE 256
int main(int argc, char* argv[]) {
   if (argc < 2) {
      printf("Usage is: client <port>\n");
      return 1;
   }

   int client_socket;
   struct sockaddr_in server_addr;

   /* Create a socket and connect it to the server */
   client_socket = socket(AF_INET, SOCK_STREAM, 0);
   server_addr.sin_family = AF_INET;
   server_addr.sin_addr.s_addr = INADDR_ANY;
   server_addr.sin_port = htons(atoi(argv[1]));
   if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
       perror("Connection failed:");
       exit(EXIT_FAILURE);
   }
   
   /* TODO (Q2.) 
    * The client simply listens to two file descriptors using the select API:
        * stdin: to read commands from the stdin and send them to the server. There are two valid commands: GET_WEATHER and EXIT.
            * If the command is EXIT, the client terminates after sending the command to the server.
        * sid: to read the response from the server and print it out on stdout.
            * If 0 bytes are received from sid, it means the server socket closed. The client should also terminate.
    * Note: do not forget to free any memory that you allocate to store the message and do not forget to close the sockets before exiting the program normally.
    */
    char buffer[MAX_BUFFER_SIZE];
    fd_set readSet;
    while (1) {
        FD_ZERO(&readSet);
        FD_SET(STDIN_FILENO, &readSet);
        FD_SET(client_socket, &readSet);
        int nbReady = select(client_socket + 1, &readSet, NULL, NULL, NULL);
        if(nbReady > 0) {
            // Check for user input from stdin
            if (FD_ISSET(STDIN_FILENO, &readSet)) {
                // Get user input
                fgets(buffer, MAX_BUFFER_SIZE, stdin);
                // Send command to server
                write(client_socket, buffer, strlen(buffer));
                if(strncmp(buffer, "EXIT", 4)==0) {
                    close(client_socket);
                    exit(0);
                }
            }
            // Check for data from server
            if (FD_ISSET(client_socket, &readSet)) {
                int bytesRead = read(client_socket, buffer, MAX_BUFFER_SIZE);
                if (bytesRead <= 0) {
                    close(client_socket);
                    exit(0);
                } else {
                    buffer[bytesRead] = '\0';
                    printf("Server Response: %s\n", buffer);
                }
            }
        }
    }
    return 0;
}
