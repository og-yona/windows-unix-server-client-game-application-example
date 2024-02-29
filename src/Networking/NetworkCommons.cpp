#include "NetworkCommons.h"

int32_t Network::sendPack(SOCKET curSocket, char* message, int32_t messageSize)
{
	return send(curSocket, message, messageSize, 0);
}
	
int32_t Network::rcevPack(SOCKET curSocket, char* buffer, int32_t bufSize)
{
	return recv(curSocket, buffer, bufSize, 0);
}
