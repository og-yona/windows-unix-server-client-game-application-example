#include "GameServer.h"

#include <iostream>

uint32_t GameServer::m_ClientId;

void GameServer::ServerLoop(int32_t portNumber)
{
    // Connection id's to assign clients for our table
    m_ClientId = 0;

    // Set up the server network to listen 
    m_ServerNetwork = new Server(portNumber);

    // Do other game server init stuff

    // Game server loop:
    while (m_ServerNetwork->IsConnected())
    {
        OnUpdate();
    }
}

void GameServer::OnUpdate()
{
    // Get new clients
    if (m_ServerNetwork->AcceptNewClient(m_ClientId))
    {
        printf("Client ID: %d - has connected to the server \n", m_ClientId);
        m_ClientId++;
    }

    // Get Packets from Clients
    ReceiveFromClients();

}

void GameServer::ReceiveFromClients()
{
    Packet packet;

    // Go through all clients
    for (const auto& client : m_ServerNetwork->m_Sessions)
    {
        // Get packet for that client
        int32_t data_length = m_ServerNetwork->ReceiveData(client.first, m_DataBuffer);

        // If no data recieved skip to next
        if (data_length <= 0)
            continue;

        // Or process the packet data
        int32_t i = 0;
        while (i < data_length)
        {
            packet.Deserialize(&(m_DataBuffer[i]));
            i += sizeof(Packet);

            switch (packet.m_PacketType)
            {
            case INIT_CONNECTION:
                printf("server received init packet from client\n");
                SendPingPackets();
                break;
            case PING:
                printf("server was pinged by client\n");
                SendPingPackets();
                break;
            default:
                printf("unknown packet type\n");
                break;

            }
        }
    }
}

void GameServer::SendPingPackets()
{
    // Send ping packet
    const unsigned int packet_size = sizeof(Packet);
    char packet_data[packet_size];

    Packet packet;
    packet.m_PacketType = PING;

    packet.Serialize(packet_data);

    m_ServerNetwork->SendToAll(packet_data, packet_size);
}

