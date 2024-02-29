#include "Server.h"
#include "ErrorCodes.h"
#ifdef _WIN32
#else
#include <fcntl.h>
#endif

Server::Server()
{
    CreateTCPServer();
}

Server::Server(int32_t portNumber)
{
    CreateTCPServer(portNumber);
}

Server::~Server()
{
}

bool Server::AcceptNewClient(uint32_t& id)
{
    // If client waiting, accept the connection and save the socket to sessions
    SOCKET ClientSocket = accept(m_ServerSocket, NULL, NULL);

    // If socket is valid, process the client
    if (ClientSocket != INVALID_SOCKET)
    {
#ifdef _WIN32
        // Disable nagle on the client's socket
        char value = 1;
        setsockopt(ClientSocket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value));
#endif
        // Insert new client into session id table
        m_Sessions.insert(std::pair<uint32_t, SOCKET>(id, ClientSocket));

        printf("Client accepted ID:%d \n", id);
        return true;
    }

    return false;
}

uint32_t Server::ReceiveData(uint32_t client_id, char* recvbuf)
{
    if (m_Sessions.find(client_id) != m_Sessions.end())
    {
        SOCKET currentSocket = m_Sessions[client_id];
        m_Result = Network::rcevPack(currentSocket, recvbuf, MAX_PACKET_SIZE);
        if (m_Result == 0)
        {
            printf("Receiving packet failed. Connection closed.\n");
            CLOSESOCKET(currentSocket);
        }
        return m_Result;
    }
    return 0;
}

void Server::SendToAll(char* packets, int totalSize)
{
    SOCKET currentSocket;

    for (const auto& client : m_Sessions)
    {
        currentSocket = client.second;
        m_Result = Network::sendPack(currentSocket, packets, totalSize);
        if (m_Result == SOCKET_ERROR)
        {
            printf("send failed with error: %s \n", Error::GetErrorMsg(m_Result));
            CLOSESOCKET(currentSocket);
        }
        printf("Server: Packet sent to clients\n");
    }
}

bool Server::CreateTCPServer(int32_t portNumber)
{
    // Reset our socket for the server
    m_ServerSocket = INVALID_SOCKET;

    // Set the address info/socket params
    ZeroMemory(&m_AddressInfo, sizeof(m_AddressInfo));
    m_AddressInfo.ai_family      = AF_INET;
    m_AddressInfo.ai_socktype    = SOCK_STREAM;
    m_AddressInfo.ai_protocol    = IPPROTO_TCP;
    m_AddressInfo.ai_flags       = AI_PASSIVE;

    // Set up the sockaddr_in structure
    m_ServerInfo.sin_family      = m_AddressInfo.ai_family;
    m_ServerInfo.sin_addr.s_addr = inet_addr(DEFAULT_SERVER_ADDRESS);
    m_ServerInfo.sin_port        = htons(portNumber);

#ifdef _WIN32
    // Init WSA WinSocket
    m_Result = WSAStartup(VERSIONREQUESTED, &m_WsaData);
    if (m_Result)
    {
        printf("WSAStartup failed with error: %d - %s \n", m_Result, Error::GetErrorMsg(m_Result));
        return false;
    }

    // Set address info pointers / get addrinfo WSA  
    m_Result = getaddrinfo(NULL, DEFAULT_PORT, &m_AddressInfo, &m_ConnectionInfo);
    if (m_Result) {
        printf("getaddrinfo failed with error: %d - %s \n", m_Result, Error::GetErrorMsg(m_Result));
        WSACleanup();
        return false;
    }
#endif
    // Create the socket
    if (!CreateSocket())
        return false;
        
    // Set non-blocking
    if (!SetSocketNonBlocking())
        return false;

    // Bind the server socket to a port
    if (!BindSocket())
        return false;

    // Start listening for incoming connections
    if (!ListenOnSocket())
        return false;

    // The server socket was created successfully
    m_IsConnected = true;
    return true;
}

bool Server::CreateSocket()
{
    static int retries = 0;        
    // Create the socket
#ifdef _WIN32
    m_ServerSocket = socket(m_ConnectionInfo->ai_family, m_ConnectionInfo->ai_socktype, m_ConnectionInfo->ai_protocol);
#else// UNIX
    m_ServerSocket = socket(m_ServerInfo.sin_family, SOCK_STREAM, IPPROTO_TCP);
#endif
    // Check for errors
    if (INVALIDSOCKET(m_ServerSocket))
    {
        // Get the error code
        m_Result = GETERROR();
        printf("Error creating socket: %d - %s", m_Result, Error::GetErrorMsg(m_Result));
        return false;
    }
    retries = 0;
    printf("Server Socket created\n");
    return true;
}

bool Server::SetSocketNonBlocking()
{
    // Set the mode of the socket to be nonblocking
#ifdef _WIN32
    u_long blocking = 1;
    m_Result = ioctlsocket(m_ServerSocket, FIONBIO, &blocking);
    if (m_Result == SOCKET_ERROR)
    {
        printf("ioctlsocket set mode failed with error: %d - %s \n", m_Result, Error::GetErrorMsg(m_Result));
        CLOSESOCKET(m_ServerSocket);
        return false;
    }
#else// UNIX
    int flags = fcntl(m_ServerSocket, F_GETFL, 0);
    fcntl(m_ServerSocket, F_SETFL, flags | O_NONBLOCK);
#endif
    printf("Server Socket set to non-blocking\n");
    return true;
}

bool Server::BindSocket()
{
    static int retries = 0;
    // Bind the socket to a local address and port
#ifdef _WIN32
    m_Result = bind(m_ServerSocket, m_ConnectionInfo->ai_addr, static_cast<int>(m_ConnectionInfo->ai_addrlen));
#else// UNIX
    m_Result = bind(m_ServerSocket, (sockaddr*)&m_ServerInfo, sizeof(m_ServerInfo));
#endif
    if (m_Result)
    {
        printf("binding socket failed with error: %d - %s \n", m_Result, Error::GetErrorMsg(m_Result));
        return false;
    }
    retries = 0;
    printf("Server Socket Bound\n");
    return true;
} 

bool Server::ListenOnSocket()
{
    static int retries = 0;

    // Start listening for incoming connections
    m_Result = listen(m_ServerSocket, SOMAXCONN);
    if (m_Result)
    {
        printf("listening on socket failed with error: %d - %s \n", m_Result, Error::GetErrorMsg(m_Result));
        return false;
    }
    retries = 0;
    printf("Server Listening on Socket...\n");
    return true;
}
