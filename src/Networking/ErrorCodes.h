#pragma once
#ifndef ERRORCODES_H
#define ERRORCODES_H

#include <unordered_map>
#include <string>

// POSIX Supplement
#ifndef _CRT_NO_POSIX_ERROR_CODES
	#define EADDRINUSE      100
	#define EADDRNOTAVAIL   101
	#define EAFNOSUPPORT    102
	#define EALREADY        103
	#define EBADMSG         104
	#define ECANCELED       105
	#define ECONNABORTED    106
	#define ECONNREFUSED    107
	#define ECONNRESET      108
	#define EDESTADDRREQ    109
	#define EHOSTUNREACH    110
	#define EIDRM           111
	#define EINPROGRESS     112
	#define EISCONN         113
	#define ELOOP           114
	#define EMSGSIZE        115
	#define ENETDOWN        116
	#define ENETRESET       117
	#define ENETUNREACH     118
	#define ENOBUFS         119
	#define ENODATA         120
	#define ENOLINK         121
	#define ENOMSG          122
	#define ENOPROTOOPT     123
	#define ENOSR           124
	#define ENOSTR          125
	#define ENOTCONN        126
	#define ENOTRECOVERABLE 127
	#define ENOTSOCK        128
	#define ENOTSUP         129
	#define EOPNOTSUPP      130
	#define EOTHER          131
	#define EOVERFLOW       132
	#define EOWNERDEAD      133
	#define EPROTO          134
	#define EPROTONOSUPPORT 135
	#define EPROTOTYPE      136
	#define ETIME           137
	#define ETIMEDOUT       138
	#define ETXTBSY         139
#define EWOULDBLOCK     140
#endif // _CRT_NO_POSIX_ERROR_CODES

namespace Error
{
	static const std::unordered_map<int, std::string> s_Errormap = {	

#ifdef _WIN32
		// Windows specific error messages here

		{ WSAEACCES, "An attempt was made to create a socket with an illegal address."},
		{ WSAEAFNOSUPPORT, "An address incompatible with the requested protocol was used."},
		{ WSAEMFILE, "No more file descriptors are available."},
		{ WSAENOBUFS, "No buffer space is available."},
		{ WSAEPROTONOSUPPORT, "The specified protocol is not supported."},
		{ WSAEPROTOTYPE, "The specified protocol is the wrong type for this socket."},
		{ WSAESOCKTNOSUPPORT, "The specified socket type is not supported in this address family."},

		{ WSAEACCES, "An attempt was made to access a socket in a way forbidden by its access permissions."},
		{ WSAEADDRINUSE, "A process on the computer is already bound to the same fully-qualified address and the socket has not been marked to allow address reuse with SO_REUSEADDR."},
		{ WSAEADDRNOTAVAIL, "The requested address is not valid in its context."},
		{ WSAEFAULT, "The system detected an invalid pointer address in attempting to use a pointer argument in a call."},
		{ WSAEINVAL, "An invalid argument was supplied."},
		{ WSAENOBUFS, "No buffer space is available."},
		{ WSAENOTSOCK, "The descriptor is not a socket."},
		{ WSAEOPNOTSUPP, "The referenced socket is not of a type that supports the bind function."},
		{ WSAEINPROGRESS, "A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function."},
		
		{ WSAEADDRINUSE, "The socket's local address is already in use and the socket was not marked to allow address reuse with SO_REUSEADDR. This error usually occurs during execution of the bind function, but could be delayed until this function if the bind was to a partially wildcard address (involving ADDR_ANY) and if a specific address needs to be committed at the time of this function."},
		{ WSAEINPROGRESS, "A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function."},
		{ WSAEINVAL, "The socket has not been bound with bind, or an unknown flag was specified, or MSG_OOB was specified for a socket with SO_OOBINLINE enabled."},
		{ WSAENOBUFS, "Not enough buffers available, too many connections."},
		{ WSAENOTSOCK, "The descriptor is not a socket."},

		{ WSAEACCES, "An attempt was made to access a socket in a way forbidden by its access permissions."},
		{ WSAEFAULT, "The system detected an invalid pointer address in attempting to use a pointer argument in a call."},
		{ WSAEINPROGRESS, "A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function."},
		{ WSAEINTR, "A blocking Windows Socket 1.1 call was canceled through WSACancelBlockingCall."},
		{ WSAEINVAL, "The listen function was not invoked prior to accept."},
		{ WSAEMFILE, "No more file descriptors are available."},
		{ WSAENOBUFS, "No buffer space is available."},
		{ WSAENOTSOCK, "The descriptor is not a socket."},
		{ WSAETIMEDOUT, "Connection timed out. A connection attempt failed because the connected party did not properly respond after a period of time, or the established connection failed because the connected host has failed to respond."},
		{ WSANOTINITIALISED, "Successful WSAStartup not yet performed. Either the application has not called WSAStartup or WSAStartup failed.The application may be accessing a socket that the current active task does not own(that is, trying to share a socket between tasks), or WSACleanup has been called too many times."},
		{ WSAEOPNOTSUPP, "The referenced socket is not of a type that supports the accept function."},
		{ WSAEWOULDBLOCK,"The socket is marked as nonblocking and no connections are present to be accepted." },
		{ WSAECONNREFUSED, "Connection refused. No connection could be made because the target computer actively refused it.This usually results from trying to connect to a service that is inactive on the foreign host�that is, one with no server application running." },
		{ WSAEISCONN, "Socket is already connected. A connect request was made on an already - connected socket.Some implementations also return this error if sendto is called on a connected SOCK_DGRAM socket(for SOCK_STREAM sockets, the to parameter in sendto is ignored) although other implementations treat this as a legal occurrence." },

#else // UNIX
		// Linux/Unix specific error messages here

		{ EACCES, "Permission to create a socket of the specified type and/or protocol is denied."},
		{ EAFNOSUPPORT, "The implementation does not support the specified address family."},
		{ EINVAL, "Unknown protocol, or protocol family not available."},
		{ EMFILE, "The process file descriptor table is full."},
		{ ENFILE, "The system file descriptor table is full."},
		{ ENOBUFS, "Insufficient resources were available to complete the call."},
		{ EPROTONOSUPPORT, "The protocol is not supported by the address family, or the protocol is not supported by the implementation."},
		
		{ EACCES, "The address is protected and the user is not the superuser."},
		{ EADDRINUSE, "The given address is already in use."},
		{ EADDRNOTAVAIL, "The specified address is not available from the local machine."},
		{ EFAULT, "The name or namelen parameter is not a valid part of the user address space."},
		{ EINVAL, "The socket is already bound to an address."},
		{ ENOBUFS, "Insufficient resources were available in the system to complete the call."},
		{ ENOMEM, "Insufficient memory was available to fulfill the request."},
		{ ENOTSOCK, "The socket argument does not refer to a socket."},
		{ EROFS, "The socket inode would reside on a read-only file system."},
		
		{ EADDRINUSE, "The address is already in use."},
		{ EBADF, "The socket is not a valid file descriptor."},
		{ EINVAL, "The socket is already bound to an address, or the protocol is not TCP."},
		{ ENOTSOCK, "The file descriptor is not associated with a socket."},
		{ EOPNOTSUPP, "The socket is not of a type that supports the listen operation."},
		{ EACCES, "The process does not have the appropriate privileges to listen on the specified port."},
			  
		{ EBADF, "The socket parameter is not within the acceptable range for a socket descriptor."},
		{ EINTR, "A signal interrupted the accept() call before any connections were available."},
		{ EINVAL, "listen() was not called for socket descriptor socket."},
		{ EMFILE, "An attempt was made to open more than the maximum number of file descriptors allowed for this process."},
		{ ENFILE, "The maximum number of file descriptors in the system are already open."},
		{ ENOBUFS, "Insufficient buffer space is available to create the new socket."},
		{ EOPNOTSUPP, "The socket type of the specified socket does not support accepting connections."},

#endif //_WIN32/UNIX

		// universal error codes:
		{ EAGAIN, "Resource temporarily unavailable" },
		{ ECONNRESET, "Connection reset by peer" },
		{ EDESTADDRREQ, "Destination address required" },
		{ EMSGSIZE, "Message too long" },
		{ ENOTCONN, "Transport endpoint is not connected" },
		{ EPIPE, "Broken pipe" },
		{ EWOULDBLOCK, "Operation would block" },
		{ EAGAIN, "The socket is marked as non-blocking and no data is waiting to be received, or the timeout time specified by the 'SO_RCVTIMEO' socket option has been exceeded."},
		{ EBADF, "The desriptor is invalid"},
		{ ECONNRESET, "The connection was reset by the peer"},
		{ EINTR, "The 'recv()' function was interrupted by a signal before any data was received."},
		{ EINVAL, "The socket is shut down or the receive buffer is empty."},
		{ ENOMEM, "There was insufficient memory available to complete the operation"},
		{ ENOTSOCK, "The descriptor does not refer to a socket."},
		{ ETIMEDOUT, "The connectiopn timed out during connection establishment, or due to a transmission timeout on an active connection."},
		{ EBADF, "The socket descriptor is not valid"},
		{ ENOTSOCK, "The descriptor is not a socket"},
		{ ENOTCONN, "The socket is not connected"},
		{ EINVAL, "The how parameter is invalid"},
		{ ENOBUFS, "No buffer space is available"},
		{ EACCES, "The calling process does not have the appropriate privileges"},
		{ EFAULT, "The socket address structure points to invalid memory"},
		{ EINPROGRESS, "A blocking socket call is in progress"},
		{ EINTR, "The function was interrupted by a signal that was caught"}
	};

	static const char* s_Unknown = "Unknown Error Code";
	static const char* GetErrorMsg(int errorcode)
	{
		for (const auto& error : s_Errormap)
		{
			if (errorcode == error.first)
				return error.second.c_str();
		}
		return s_Unknown;
	}

} // namespace Error

#endif // ERRORCODES_H
