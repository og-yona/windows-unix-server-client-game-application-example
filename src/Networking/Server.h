#pragma once
#ifndef SERVER_H
#define SERVER_H

#include "NetworkCommons.h"
#include "NetworkException.h"
#include "Packets.h"

#include <map>
#include <string>

class Server
{
public:
	// (de)Constructors
    Server();
	Server(int32_t portNumber);
    ~Server();

	// Accept new connections
	bool AcceptNewClient(uint32_t& id);

	// Receive incoming data from all clients
	uint32_t ReceiveData(uint32_t client_id, char* recvbuf);

	// Send data to all clients
	void SendToAll(char* packets, int totalSize);

	// Map to keep track of each client's socket
	std::map<uint32_t, SOCKET> m_Sessions;

	// Returns state of server
	bool IsConnected() { return m_IsConnected; }
private:
	// Private functions for creating the server socket and start listening it:

	// Creates a server using the specified port number and server type
	bool CreateTCPServer(int32_t portNumber = DEFAULT_PORT_INT);
		
	// Creates a socket 
	bool CreateSocket();

	// Creates a socket 
	bool SetSocketNonBlocking();

	// Bind the server socket to a port
	bool BindSocket();

	// Start listening for incoming connections
	bool ListenOnSocket();

private:
	// Private data variables

	// Status of the server
	bool m_IsConnected = false;
		
#ifdef _WIN32
	// Windows socket data:
	WSADATA m_WsaData;
#endif
	// Server data:
	addrinfo m_AddressInfo;
	addrinfo* m_ConnectionInfo;
	SOCKET m_ServerSocket;
	sockaddr_in m_ServerInfo;
    
	int32_t m_Result;// for error checking return values   
};

#endif//SERVER_H