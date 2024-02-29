#pragma once
#ifndef NETWORK_H
#define NETWORK_H
#include "Packets.h"

#include <memory.h>
#include <stdint.h>
#include <stdio.h> // standard input and output library

#ifdef _WIN32
	#include <WinSock2.h>
	#include <ws2tcpip.h>

	#pragma comment (lib, "Ws2_32.lib")
	#pragma comment (lib, "Mswsock.lib")
	#pragma comment (lib, "AdvApi32.lib")

	#ifndef _NETWORK_MACROS_
		#define _NETWORK_MACROS
		#define VERSIONREQUESTED MAKEWORD(2,2)
		#define INVALIDSOCKET(s) ((s) == INVALID_SOCKET)
		#define GETERROR() (WSAGetLastError())
		#define CLOSESOCKET(s) (closesocket(s))
	#endif
#else // UNIX
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <errno.h>
	#include <arpa/inet.h>
	#include <unistd.h>
	#include <bits/stdc++.h>
	#include <netdb.h>
	#include <stdlib.h>

	#ifndef _NETWORK_MACROS_
		#define _NETWORK_MACROS_
		#define SOCKET int
		#define SOCKET_ERROR -1
		#define INVALIDSOCKET(s) ((s) < 0)
		#define GETERROR() (errno)
		#define CLOSESOCKET(s) (close(s))
		#define ZeroMemory(dest, count) (memset(dest,0,count))
		typedef const char* PCSTR;
	#endif
#endif // _WIN32/UNIX

#ifndef INVALID_SOCKET
	#define INVALID_SOCKET -1
#endif

#ifndef ZeroMemory
	#define ZeroMemory(destination,length) memset((destination),0,(length))
#endif

// Default retry amount for connecting
#define DEFAULT_RETRY_CONNECT_AMOUNT 5

// Size of our buffer
#define DEFAULT_BUFLEN 512

// Default port used to connect sockets 
#define DEFAULT_PORT "6881"
#define DEFAULT_PORT_INT 6881

// Default client/server addresses = localhost
#define DEFAULT_SERVER_ADDRESS "127.0.0.1"
#define DEFAULT_CLIENT_CONNECT_TO_ADDRESS "127.0.0.1"

// Network shared functions class:
class Network
{
public:
	static int32_t sendPack(SOCKET curSocket, char* message, int32_t messageSize);
	static int32_t rcevPack(SOCKET curSocket, char* buffer, int32_t bufSize);
};


#endif // NETWORK_H