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
#include <vector>
#include <cstring>

class PacketCoder {
public:
    static int readVarInt(int socket_fd);
    static char readByte(int socket_fd);
    static char* readString(int socket_fd);
    static short readShort(int socket_fd);
    static unsigned short readUnsignedShort(int socket_fd);
    static long long readLong(int socket_fd);

    static void writeVarInt(std::vector<char> *buffer, int input);
    static void writeByte(std::vector<char> *buffer, char input);
    static void writeString(std::vector<char> *buffer, char* input);
    static void writeLong(std::vector<char> *buffer, long input);
private:
};
