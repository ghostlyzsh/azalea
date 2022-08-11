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
#include "uuid.h"

class PacketCoder {
public:
    static int readVarInt(int socket_fd);
    static char readByte(int socket_fd);
    static char* readString(int socket_fd);
    static short readShort(int socket_fd);
    static unsigned short readUnsignedShort(int socket_fd);
    static long long readLong(int socket_fd);
    static bool readBool(int socket_fd);
    static char* readByteArray(int socket_fd, int length);
    static UUID readUUID(int socket_fd);

    static void writeVarInt(std::vector<char> *buffer, int input);
    static void writeByte(std::vector<char> *buffer, char input);
    static void writeString(std::vector<char> *buffer, char* input);
    static void writeLong(std::vector<char> *buffer, long input);
    static void writeUUID(std::vector<char> *buffer, UUID input);
    static void writeShort(std::vector<char> *buffer, short value);
    static void writeUnsignedShort(std::vector<char> *buffer, unsigned short value);
    static void writeUnsignedByte(std::vector<char> *buffer, unsigned char input);
    static void writeBool(std::vector<char> *buffer, bool value);

    // ===================================
    // ========= tag functions ===========
    // ===================================
    static void readTagByte(int socket_fd);

    static int zeroAmount;

};
