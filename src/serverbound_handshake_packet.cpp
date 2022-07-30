#include "serverbound_handshake_packet.h"

void ServerboundHandshakePacket::read(int socket_fd) {
    this->protocol_version = PacketCoder::readVarInt(socket_fd);
    this->address = PacketCoder::readString(socket_fd);
    this->port = PacketCoder::readUnsignedShort(socket_fd);
    this->next_state = PacketCoder::readVarInt(socket_fd);
}

void ServerboundHandshakePacket::log() {
    std::cout << "Protocol Version: " << this->protocol_version << "\nServer Address: "
        << this->address << "\nPort: " << this->port << "\nNext State: " << this->next_state << std::endl;
}
