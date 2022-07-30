#pragma once
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <iostream>
#include "packet_coder.h"
#include "serverbound_handshake_packet.h"
#include "clientbound_status_response_packet.h"
#include "serverbound_ping_request_packet.h"
#include "clientbound_pong_response_packet.h"

class ClientHandler {
public:
    ClientHandler(int server_fd, struct sockaddr_in address, int addrlen);

protected:
    void *run_socket();
private:
    static void* run_socket_func(void* arg) {((ClientHandler*)arg)->run_socket(); return NULL;}

    int socket_fd;
    pthread_t thread;
};
