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

    // Call Run to actually start the server, includes server game loop
    void ServerLoop(int32_t portNumber = DEFAULT_PORT_INT);

    // Per frame update function
    void OnUpdate(); 

private:
    // Receive data from clients
    void ReceiveFromClients();

    // Send ping to all clients
    void SendPingPackets();

private:        
    static uint32_t m_ClientId; // IDs for the clients connecting for table in ServerNetwork         
    Server* m_ServerNetwork; // The ServerNetwork object         
    char m_DataBuffer[MAX_PACKET_SIZE]; // data buffer
};


#endif // GAMESERVER_H