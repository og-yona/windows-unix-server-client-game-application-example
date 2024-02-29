#include "GameClient.h"

GameClient::GameClient()
{
	ConnectTo(DEFAULT_CLIENT_CONNECT_TO_ADDRESS, DEFAULT_PORT_INT);
}

GameClient::GameClient(char* host, int32_t portNumber)
{
	ConnectTo(host, portNumber);
}

void GameClient::ConnectTo(char* host, int32_t portNumber)
{
	// Connect to the server by creating a new Client
	m_ClientNetwork = new Client(host, portNumber);

	// If connected: Send init packet and start client game loop
	if (m_ClientNetwork->m_ClientConnected)
	{
		const unsigned int packet_size = sizeof(Packet);
		char packet_data[packet_size];

		Packet packet;
		packet.m_PacketType = INIT_CONNECTION;

		packet.Serialize(packet_data);

		Network::sendPack(m_ClientNetwork->GetSocket(), packet_data, packet_size);
		printf("Client: Sending init connection packet\n");

		// Start the client game loop
		ClientLoop();
	}
}

GameClient::~GameClient(void)
{
}

void GameClient::ClientLoop()
{
	while (m_ClientNetwork->m_ClientConnected)
	{
		//do game stuff
		OnUpdate();
	}
}

void GameClient::SendPingPacket()
{
	// Create and send a simple ping packet
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.m_PacketType = PING;

	packet.Serialize(packet_data);

	Network::sendPack(m_ClientNetwork->GetSocket(), packet_data, packet_size);
	printf("Client: pinging server\n");
}

void GameClient::OnUpdate()
{
	// Get the server packet/data 
	Packet packet;
	int32_t data_length = m_ClientNetwork->ReceivePackets(m_DataBuffer);

	// Return if no data recieved
	if (data_length <= 0)
		return;

	// Or process the packet data
	int32_t i = 0;
	while (i < data_length)
	{
		packet.Deserialize(&(m_DataBuffer[i]));
		i += sizeof(Packet);

		switch (packet.m_PacketType)
		{
			case PING:
				printf("client: was pinged by server\n");
				SendPingPacket();
				break;

			default:
				printf("client: error in packet type\n");
				break;
		}
	}
} // void GameClient::OnUpdate()
