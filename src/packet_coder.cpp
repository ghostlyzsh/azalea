#include "packet_coder.h"

int PacketCoder::readVarInt(int socket_fd) {
    int value = 0;
    int position = 0;
    char currentByte;

    while(true) {
        currentByte = PacketCoder::readByte(socket_fd);
        value |= (currentByte & 0x7F) << position;

        if((currentByte & 0x80) == 0) break;

        position += 7;

        if(position >= 32) {
            //std::cout << "VarInt is too big." << std::endl;
            return 0;
        }
    }

    return value;
}

char* PacketCoder::readString(int socket_fd) {
    int length = PacketCoder::readVarInt(socket_fd);
    char* string = (char*)malloc(length * sizeof(char));
    for(int i = 0; i < length; i++) {
        string[i] = PacketCoder::readByte(socket_fd);
    }
    return string;
}

short PacketCoder::readShort(int socket_fd) {
    short result = 0;
    result |= (PacketCoder::readByte(socket_fd) & 0xFF) << 8;
    result |= (PacketCoder::readByte(socket_fd) & 0xFF);
    return result;
}
unsigned short PacketCoder::readUnsignedShort(int socket_fd) {
    return (unsigned short) PacketCoder::readShort(socket_fd);
}

long long PacketCoder::readLong(int socket_fd) {
    long long result = 0;
    result |= (PacketCoder::readByte(socket_fd) & 0xFF) << 56;
    result |= (PacketCoder::readByte(socket_fd) & 0xFF) << 48;
    result |= (PacketCoder::readByte(socket_fd) & 0xFF) << 40;
    result |= (PacketCoder::readByte(socket_fd) & 0xFF) << 32;
    result |= (PacketCoder::readByte(socket_fd) & 0xFF) << 24;
    result |= (PacketCoder::readByte(socket_fd) & 0xFF) << 16;
    result |= (PacketCoder::readByte(socket_fd) & 0xFF) << 8;
    result |= (PacketCoder::readByte(socket_fd) & 0xFF);
    return result;
}

char PacketCoder::readByte(int socket_fd) {
    char buf;
    recv(socket_fd, &buf, 1, MSG_WAITALL);
    return buf;
}

void PacketCoder::writeVarInt(std::vector<char> *buffer, int value) {
    while(true) {
        if((value & ~0x7F) == 0) {
            PacketCoder::writeByte(buffer, value);
            return;
        }

        writeByte(buffer, (value & 0x7F) | 0x80);

        unsigned int uvalue = (unsigned int) value;
        uvalue >>= 7;
        value = (int) uvalue;
    }
}
void PacketCoder::writeString(std::vector<char> *buffer, char* value) {
    int length = sizeof(value);
    PacketCoder::writeVarInt(buffer, length);
    for(int i = 0; i < length; i++) {
        PacketCoder::writeByte(buffer, value[i]);
    }
}

void PacketCoder::writeLong(std::vector<char> *buffer, long value) {
    long operatingValue;
    for (int i = 0; i < 8; i++) {
        operatingValue = value >> (i * 8);
        PacketCoder::writeByte(buffer, (char) (operatingValue & 0xFF));
    }
}

void PacketCoder::writeByte(std::vector<char> *buffer, char input) {
    buffer->push_back(input);
}