#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <errno.h>

#define MAX_BUFFER_SIZE 256
#define MAX_CLIENTS 10

typedef struct {
    float temperature;
    float humidity;
    float pressure;
} WeatherData;

int main(int argc, char* argv[]) {
    if (argc < 2) {
      printf("Usage is: server <port>\n");
      return 1;
    }

    /* Create server socket and bind it to the address */
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(atoi(argv[1]));
        if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Socket bind failed");
        exit(EXIT_FAILURE);
    }

    /* Initialize weather data */
    WeatherData current_weather;
    current_weather.temperature = 0.0;
    current_weather.humidity = 0.0;
    current_weather.pressure = 0.0;

    /* Listen for incoming connections */
    if (listen(server_socket, MAX_CLIENTS) == -1) {
        perror("Socket listen failed");
        exit(EXIT_FAILURE);
    }

    int client_sockets[MAX_CLIENTS];     /* an array to store the socket ids (fd) for each client */
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        client_sockets[i] = -1;
    }
   /* TODO (Q2.)
    * Given n client sockets and the server socket, the server simply needs to listen to all of them using the select API. 
    * Initially, there are no client sockets. Therefore, the server only listens to sid. 
    * If the server socket is ready, it implies a client is trying to connect. Server accepts the request and expands the set of file descriptors to listen to.
    * If any of the client sockets are ready, it reads the message and sends an appropriate response to all the clients. 
        * If the message is GET_WEATHER, it updates the current_weather and sends it to all clients.
            * temperature is incremented by 1, humidity is incremented by 2 and pressure is incremented by 3.
        * If the message is EXIT, the server closes all client sockets as well as the server socket.
        * If the message is anything else, server sends the message "Invalid command" to the client that sent the message.
    * Note: do not forget to free any memory that you allocate to store the message received and do not forget to close the sockets before exiting the program normally.
   */
    int numClients = 0;
    fd_set readfds;
    int maxSocket;
    char buffer[MAX_BUFFER_SIZE];
    while (1) {
        FD_ZERO(&readfds);
        FD_SET(server_socket, &readfds);
        maxSocket = server_socket;
        // set any sockets that exist
        for (int i = 0; i < MAX_CLIENTS; ++i) {
            if (client_sockets[i] != -1) {
                FD_SET(client_sockets[i], &readfds);
                maxSocket = client_sockets[i] > maxSocket ? client_sockets[i] : maxSocket;
            }
        }
        
        // Use select to monitor sockets for activity
        int nbReady = select(maxSocket + 1, &readfds, NULL, NULL, NULL);
        if(nbReady > 0) {
            // Check for incoming connection
            if (FD_ISSET(server_socket, &readfds)) {
                if (numClients < MAX_CLIENTS) {
                    struct sockaddr_in client;
                    socklen_t clientSize = sizeof(client);
                    int i = 0;
                    for (; client_sockets[i] != -1; ++i) {} // find available slot
                    client_sockets[i] = accept(server_socket, (struct sockaddr *)&client, &clientSize);
                    if (client_sockets[i] == -1) {
                        printf("We tried to accept a socket but there was an error: %s\n", strerror(errno));
                    }
                    else {
                        printf("We accepted a socket: %d\n", client_sockets[i]);
                        numClients++;
                    }
                    
                } else {
                    printf("Connection refused. Maximum number of clients connected.\n");
                }
            }

            // Loop through client slots and check for messages
            for (int i = 0; i < MAX_CLIENTS; ++i) {
                if (client_sockets[i] != -1 && FD_ISSET(client_sockets[i], &readfds)) {
                    int bytesRead = read(client_sockets[i], buffer, MAX_BUFFER_SIZE);
                    if (bytesRead <= 0) {
                        // client disconnected, free slot
                        close(client_sockets[i]);
                        client_sockets[i] = -1;
                        numClients--;
                    }
                    else {
                        if (strncmp(buffer, "EXIT", 4) == 0) {
                            //close open sockets
                            for (int i = 0; i < MAX_CLIENTS; ++i) {
                                if (client_sockets[i] != -1) close(client_sockets[i]);
                            }
                            close(server_socket);
                            exit(0);
                        }
                        else if (strncmp(buffer, "GET_WEATHER", 11) == 0) {
                            current_weather.temperature += 1;
                            current_weather.humidity += 2;
                            current_weather.pressure += 3;
                            sprintf(buffer, "Temperature: %.2f, Humidity: %.2f, Pressure: %.2f", current_weather.temperature, current_weather.humidity, current_weather.pressure);
                            // write output to all clients
                            for (int i = 0; i < MAX_CLIENTS; ++i) {
                                if (client_sockets[i] != -1) {
                                    write(client_sockets[i], buffer, strlen(buffer));
                                }
                            }
                
                        }
                        else {
                            sprintf(buffer, "Invalid command");
                            write(client_sockets[i], buffer, strlen(buffer));
                        }
                    }
                }
            }
        }
    }
    return 0;
}
