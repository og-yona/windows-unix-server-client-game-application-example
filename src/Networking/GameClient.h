#pragma once
#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include "Client.h"
#include "Packets.h"

class GameClient 
{
public:
	GameClient();
	GameClient(char* host, int32_t portNumber);
	~GameClient();

	// Client loop / get the server packet data
	void ClientLoop();
	void OnUpdate();

	Client* m_ClientNetwork;
	char m_DataBuffer[MAX_PACKET_SIZE];

private:
	void SendPingPacket();
	void ConnectTo(char* host, int32_t portNumber);
};

#endif // GAMECLIENT_H