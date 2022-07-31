#include "clientbound_login_success_packet.h"

void ClientboundLoginSuccessPacket::write(char* username) {
    UUID emptyUUID(0, 0);

    std::vector<char> length_buffer;

    PacketCoder::writeVarInt(&length_buffer, 2);
    PacketCoder::writeUUID(&length_buffer, emptyUUID);
    PacketCoder::writeString(&length_buffer, username);
    PacketCoder::writeVarInt(&length_buffer, 0);

    PacketCoder::writeVarInt(&buffer, length_buffer.size());
    PacketCoder::writeVarInt(&buffer, 2);
    PacketCoder::writeUUID(&buffer, emptyUUID);
    PacketCoder::writeString(&buffer, username);
    PacketCoder::writeVarInt(&buffer, 0);
}

void ClientboundLoginSuccessPacket::send(int socket_fd) {
    size_t size = this->buffer.size();
    ::send(socket_fd, static_cast<void*>(&this->buffer[0]), size, MSG_NOSIGNAL);
}
