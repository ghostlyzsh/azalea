#include "clientbound_status_response_packet.h"

void ClientboundStatusResponsePacket::write() {
    char* data = "{\
                \"version\": {\
                \"name\": \"1.19\",\
                \"protocol\": 759\
                },\
                \"players\": {\
                \"max\": 20,\
                \"online\": 0\
                },\
                \"description\": {\
                \"text\": \"Azalea Server\"\
                }\
                }";

    std::vector<char> length_buffer;

    PacketCoder::writeVarInt(&length_buffer, 0x00);
    PacketCoder::writeString(&length_buffer, data);

    //length
    PacketCoder::writeVarInt(&(this->buffer), length_buffer.size());

    // write packet id
    PacketCoder::writeVarInt(&(this->buffer), 0x00);

    // write json
    PacketCoder::writeString(&(this->buffer), data);
}
void ClientboundStatusResponsePacket::send(int socket_fd) {
    size_t size = this->buffer.size();
    ::send(socket_fd, static_cast<void*>(&this->buffer[0]), size, MSG_NOSIGNAL);
}
