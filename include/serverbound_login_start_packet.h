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

class ServerboundLoginStartPacket {
public:
    void read(int socket_fd);
    
    void log();

    char* username;
    bool hasSignatureData;

    // signature data
    long timestamp;
    int pubKeyLength;
    char* pubKey;
    int signatureLength;
    char* signature;
};
