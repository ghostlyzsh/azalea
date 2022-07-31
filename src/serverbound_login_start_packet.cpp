#include "serverbound_login_start_packet.h"

void ServerboundLoginStartPacket::read(int socket_fd) {
    this->username = PacketCoder::readString(socket_fd);
    this->hasSignatureData = PacketCoder::readBool(socket_fd);
    if(this->hasSignatureData) {
        this->timestamp = PacketCoder::readLong(socket_fd);
        this->pubKeyLength = PacketCoder::readVarInt(socket_fd);
        this->pubKey = PacketCoder::readByteArray(socket_fd, this->pubKeyLength);
        this->signatureLength = PacketCoder::readVarInt(socket_fd);
        this->signature = PacketCoder::readByteArray(socket_fd, this->signatureLength);
    }
}

void ServerboundLoginStartPacket::log() {
    std::cout << "Player with username: \"" << this->username << "\" joined the game." << std::endl;
}
