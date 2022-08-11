#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include "client_handler.h"
#include "entity/entity_handler.h"
#include <iostream>
#include <sys/select.h>

#define PORT 25566

int PacketCoder::zeroAmount = 0;

int EntityHandler::currentId = 0;

int server_fd;

int main(int argc, char const* argv[]) {
    int socket_fd, valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Server creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if(bind(server_fd, (struct sockaddr*)&address, sizeof(address)) == -1) {
        perror("The server could not bind to port 25566. Try using a different port.");
        exit(EXIT_FAILURE);
    }

    if(listen(server_fd, 3) == -1) {
        perror("The server failed to beging listening for clients.");
        exit(EXIT_FAILURE);
    }

    // TODO: add server.properties

    while(true) {
        ClientHandler handler(server_fd, address, addrlen);
    }

    return 0;
}
