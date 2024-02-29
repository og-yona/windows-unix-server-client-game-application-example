#pragma once
#ifndef NETWORKEXCEPTION_H
#define NETWORKEXCEPTION_H
#ifndef _WIN32
#ifndef SOCKET
#define SOCKET int
#endif
#else
#include <WinSock2.h>
#endif

#include <exception>
#include <string>
#include <unordered_map>

namespace SS {

	enum class ExceptionType
	{
		Socket	  = 0,
		Bind	  = 1,
		Listen	  = 2,
		Accept	  = 3,
		Send	  = 4,
		Receive	  = 5,
		Shutdown  = 6,
		Unknown	  = -1,
	};

	static const std::unordered_map<ExceptionType, std::string> s_ExceptionMap = {
		{ExceptionType::Socket,  "Socket"},
		{ExceptionType::Bind,    "Bind"},
		{ExceptionType::Listen,  "Listen"},
		{ExceptionType::Accept,  "Accept"},
		{ExceptionType::Send,    "Send"},
		{ExceptionType::Receive, "Receive"},
		{ExceptionType::Unknown, "Unknown"},
	};

	class NetworkException : public std::exception
	{
	public:
		NetworkException(ExceptionType type, SOCKET socket, int errorCode, const std::string& message) :
			m_Socket(socket), m_ErrorCode(errorCode), m_Type(type), m_Message(message) 
		{
		}

		const char* what() const noexcept override 
		{
			return m_Message.c_str();
		}

		SOCKET GetSocket() 
		{
			return m_Socket;
		}

		int GetErrorCode() 
		{
			return m_ErrorCode;
		}

		static ExceptionType GetTypeByName(const std::string& typeName)
		{
			for (const auto& types : s_ExceptionMap)
			{
				if (types.second == typeName)
					return types.first;
			}
			return ExceptionType::Unknown;
		}

		static const std::string& GetTypeName(ExceptionType type) 
		{
			for (const auto& types : s_ExceptionMap)
			{
				if (types.first == type)
					return types.second;
			}
			return s_ExceptionMap.at(ExceptionType::Unknown);
		}

	private:
		SOCKET m_Socket;
		int m_ErrorCode;
		ExceptionType m_Type;
		std::string m_Message;
	};

} // namespace SS

#endif // NETWORKEXCEPTION_H