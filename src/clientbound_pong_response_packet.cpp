#include "clientbound_pong_response_packet.h"

void ClientboundPongResponsePacket::write(long long payload) {
    std::vector<char> length_buffer;

    PacketCoder::writeVarInt(&length_buffer, 3);
    PacketCoder::writeVarInt(&length_buffer, 8);

    //length
    PacketCoder::writeVarInt(&(this->buffer), length_buffer.size());

    // write packet id
    PacketCoder::writeVarInt(&(this->buffer), 0x01);

    PacketCoder::writeLong(&(this->buffer), payload);
}

void ClientboundPongResponsePacket::send(int socket_fd) {
    size_t size = this->buffer.size();
    ::send(socket_fd, static_cast<void*>(&this->buffer[0]), size, MSG_NOSIGNAL);
}
