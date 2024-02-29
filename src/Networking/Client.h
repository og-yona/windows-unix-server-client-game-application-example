#pragma once
#ifndef CLIENT_H
#define CLIENT_H

#include "NetworkCommons.h"
#include "Packets.h"

class Client
{
public:
	// (de)Constructors
	Client();
	Client(char* host, int32_t portNumber);
	~Client();

	// Get the data packets from the server
	int32_t ReceivePackets(char* recvbuf);

	// Returns client socket
	SOCKET GetSocket() { return m_ConnectionSocket; }

	// Keep track of if we are connected to the server
	bool m_ClientConnected = false;

private:
	// Private functions for creating the socket and connecting to the server

	void ConnectTCPServer(char* host = (char*)DEFAULT_CLIENT_CONNECT_TO_ADDRESS, int32_t portNumber = DEFAULT_PORT_INT);
	bool WSAInit();
	bool CreateTCPSocket(char* host, int32_t portNumber);
	bool ConnectToSocket();

private:
	// Private data variables:

#ifdef _WIN32
	// Windows-specific data for socket initialization.
	WSADATA m_WsaData;
#endif
	// For error checking function calls
	int32_t m_Result;

	// Address information for the client socket.
	addrinfo m_AddressInfo;
	addrinfo* m_HostAddressInfo;

	// Socket for client to connect to server
	SOCKET m_ConnectionSocket;
};


#endif // CLIENT_H