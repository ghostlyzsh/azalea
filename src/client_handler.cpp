#include "client_handler.h"

ClientHandler::ClientHandler(int server_fd, struct sockaddr_in address, int addrlen) {
    this->socket_fd = accept(server_fd, (struct sockaddr*) &address, (socklen_t*) &addrlen);
    if(this->socket_fd == -1) {
        perror("Error with client connecting.");
        exit(EXIT_FAILURE);
    }

    int rc = pthread_create(&thread, NULL, run_socket_func, this);
}

void* ClientHandler::run_socket() {
    std::cout << "Client connected" << std::endl;

    bool connected = true;
    int state = 0;
    while(connected) {
        int length = PacketCoder::readVarInt(this->socket_fd);
        int id = PacketCoder::readVarInt(this->socket_fd);
        //std::cout << length << std::endl;
        //std::cout << id << std::endl;

        switch(id) {
            case 0:
                if(state == 0) {
                    ServerboundHandshakePacket packet;
                    packet.read(this->socket_fd);
                    state = packet.next_state;
                } else if(state == 1) {
                    // status packet
                    ClientboundStatusResponsePacket packet;
                    packet.write();
                    packet.send(this->socket_fd);
                } else if (state == 2) {
                    ServerboundLoginStartPacket packet;
                    packet.read(this->socket_fd);
                    packet.log();

                    ClientboundLoginSuccessPacket packetOut;
                    packetOut.write(packet.username);
                    packetOut.send(this->socket_fd);
                }
                break;
            case 1:
                ServerboundPingRequestPacket packet;
                packet.read(this->socket_fd);
                
                ClientboundPongResponsePacket packetOut;
                packetOut.write(packet.payload);
                packetOut.send(this->socket_fd);
                close(this->socket_fd);
                pthread_exit(&this->thread);
                break;
        }

    }

    close(this->socket_fd);
    pthread_exit(&this->thread);
    return NULL;
}
