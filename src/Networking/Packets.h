#pragma once
#ifndef PACKET_H
#define PACKET_H

#include <stdio.h> // standard input and output library
#include <stdint.h>
#include <memory.h>

#define MAX_PACKET_SIZE 1024//1000000

enum PacketTypes {
    INIT_CONNECTION = 0,
    PING = 1,
};

struct Packet {
    uint32_t m_PacketType;

    void Serialize(char* data) {
        memcpy(data, this, sizeof(Packet));
    }

    void Deserialize(char* data) {
        memcpy(this, data, sizeof(Packet));
    }
};

#endif // PACKET_H