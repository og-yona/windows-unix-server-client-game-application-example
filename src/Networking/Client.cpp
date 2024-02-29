#include "Client.h"
#include "ErrorCodes.h"

Client::Client() 
{
    ConnectTCPServer();
}

Client::Client(char* host, int32_t portNumber)
{
    ConnectTCPServer(host, portNumber);
}

Client::~Client()
{
}

void Client::ConnectTCPServer(char* host, int32_t portNumber)
{
    if (!WSAInit())
        return;

    if (!CreateTCPSocket(host, portNumber))
        return;

    if (!ConnectToSocket())
        return;          
}

bool Client::WSAInit()
{
#ifdef _WIN32
    // Initialize the Windows Sockets DLL
    m_Result = WSAStartup(VERSIONREQUESTED, &m_WsaData);
    // If there was an error, throw an exception
    if (m_Result)
    {
        printf("WSAStartup failed with error: %d - %s \n", m_Result, Error::GetErrorMsg(m_Result));
        return false;
    }
#endif
    return true;
}

bool Client::CreateTCPSocket(char* host, int32_t portNumber)
{
    // Clear address info & Set socket params:
    ZeroMemory(&m_AddressInfo, sizeof(m_AddressInfo));        
    m_AddressInfo.ai_family   = AF_INET;      
    m_AddressInfo.ai_socktype = SOCK_STREAM;
    m_AddressInfo.ai_protocol = IPPROTO_TCP;

    // Get the address info for the specified host and port
    std::string Port = std::to_string(portNumber);
    m_Result = getaddrinfo((PCSTR)host, Port.c_str(), (const addrinfo*)&m_AddressInfo, &m_HostAddressInfo);
    Port.erase();

    // If there is error, print it and return false
    if (m_Result)
    {
        printf("Get the address info failed with error: %d - %s \n", m_Result, Error::GetErrorMsg(m_Result));
#ifdef _WIN32
        WSACleanup();
#endif
        return false;
    }

    // Create a socket using the address info
    m_ConnectionSocket = socket(m_HostAddressInfo->ai_family, m_HostAddressInfo->ai_socktype, m_HostAddressInfo->ai_protocol);

    // If the socket is invalid, get & print error and return false
    if (INVALIDSOCKET(m_ConnectionSocket))
    {
        m_Result = GETERROR();
        printf("Get the address info failed with error: %d - %s \n", m_Result, Error::GetErrorMsg(m_Result));
#ifdef _WIN32
        WSACleanup();
#endif
        return false;
    }

    // Return true when socket was created successfully
    return true;

} 

bool Client::ConnectToSocket()
{
    // Try to connect for set retry amount before giving up
    for (size_t retries = 0; retries < DEFAULT_RETRY_CONNECT_AMOUNT; retries++)
    { 
        m_Result = connect(m_ConnectionSocket, m_HostAddressInfo->ai_addr, m_HostAddressInfo->ai_addrlen);
        if (m_Result)
        {
            m_Result = GETERROR();
            printf(" Coult not connect: %d - %s \n ", m_Result, Error::GetErrorMsg(m_Result));
            printf("... Retrying : %d / %d \n ", (int)(retries+1), DEFAULT_RETRY_CONNECT_AMOUNT);
            continue;
        }
        break;
    }

    // If there was an error, print error and exit function
    if (m_Result)
    {
        m_Result = GETERROR();
        printf(" Coult not connect: %d - %s \n", m_Result, Error::GetErrorMsg(m_Result));
        CLOSESOCKET(m_ConnectionSocket);
#ifdef _WIN32
        WSACleanup();
#endif
        return false;
    }

    // Return true if the connection was successful
    m_ClientConnected = true;
    return true;
}

// Receive packets from the server
int32_t Client::ReceivePackets(char* recvbuf)
{
    m_Result = Network::rcevPack(m_ConnectionSocket, recvbuf, MAX_PACKET_SIZE);
    if (m_Result == 0)
    {
        printf("Connection closed\n");
        CLOSESOCKET(m_ConnectionSocket);
#ifdef _WIN32
        WSACleanup();
#endif
        std::exit(EXIT_FAILURE);
    }

    return m_Result;
}
