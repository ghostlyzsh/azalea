#pragma once

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include "packet_coder.h"
#include <iostream>

class ServerboundHandshakePacket {
public:
    void read(int socket_fd);
    
    void log();

    int protocol_version;
    char* address;
    unsigned short port;
    int next_state;
};
