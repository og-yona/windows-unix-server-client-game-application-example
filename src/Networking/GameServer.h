#pragma once
#ifndef GAMESERVER_H
#define GAMESERVER_H

#include "Server.h"
#include "Packets.h"

class GameServer
{

public:
    GameServer() = default;
    ~GameServer() = default;

    // Call ServerLoop to actually start the GameServer
    void ServerLoop(int32_t portNumber = DEFAULT_PORT_INT);

    // Per frame update function
    void OnUpdate(); 

private:
    // Receive data from clients
    void ReceiveFromClients();

    // Send ping to all clients
    void SendPingPackets();

private:        
    static uint32_t m_ClientId;         // Current/next ID for the clients connecting for table in ServerNetwork         
    Server* m_ServerNetwork;            // Actual TCP Server        
    char m_DataBuffer[MAX_PACKET_SIZE]; // Data buffer
};


#endif // GAMESERVER_H