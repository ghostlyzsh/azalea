#include "serverbound_ping_request_packet.h"

void ServerboundPingRequestPacket::read(int socket_fd) {
    this->payload = PacketCoder::readLong(socket_fd);
}

void ServerboundPingRequestPacket::log() {
    std::cout << "Payload: " << this->payload << std::endl;
}
