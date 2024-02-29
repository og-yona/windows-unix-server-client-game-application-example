#include "Networking/GameServer.h"
#include "Networking/GameClient.h"

#include <iostream>
#include <thread>

int main(int argc, char** argv[])
{
	std::cout << "Hello world!" << std::endl;

	std::cout << "Type in startup mode" << std::endl;
	std::cout << "h : headless/server only" << std::endl;
	std::cout << "c : connect to server as client" << std::endl;
	std::cout << "s : start local server and connect to it" << std::endl;
	std::cout << " >";

	std::string input;
	std::cin >> input;

	if (input == "h")
	{
		GameServer server = GameServer();
		server.ServerLoop(6881);
	}

	if (input == "c")
		GameClient client = GameClient("127.0.0.1", 6881);

	if (input == "s")
	{
		GameServer server;
		std::thread serverThread(&GameServer::ServerLoop, &server, 6881);
		GameClient client = GameClient("127.0.0.1", 6881);
		serverThread.join();
	}

	return 0;
}
