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
#include <cstring>

class ClientboundStatusResponsePacket {
public:
    void write();

    void send(int socket_fd);
private:
    std::vector<char> buffer;
};
