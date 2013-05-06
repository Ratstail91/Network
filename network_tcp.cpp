#include "network.hpp"

#include <cstdio>

/* TCPSocket definition
*/

TCPSocket::TCPSocket() {
	sock = INVALID_SOCKET;
}

TCPSocket::TCPSocket(const char* ip, int port) {
	Open(ip, port);
}

TCPSocket::~TCPSocket() {
	Close();
}

int TCPSocket::Open(const char* ip, int port) {
	addrinfo *ptr = nullptr, hints;
	char buf[100];
	sprintf(buf, "%d",port); //std compliant itoa()

	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if (getaddrinfo(ip, buf, &hints, &ptr)) {
		return -1;
	}

	sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

	if (sock == INVALID_SOCKET) {
		freeaddrinfo(ptr);
		return -2;
	}

	for(addrinfo *it = ptr; it; it = it->ai_next) {
		if (connect(sock, it->ai_addr, it->ai_addrlen) == SOCKET_ERROR) {
			sock = INVALID_SOCKET;
		}
	}

	freeaddrinfo(ptr);

	if (sock == INVALID_SOCKET) {
		closesocket(sock);
		sock = INVALID_SOCKET;
		return -3;
	}
	return 0;
}

void TCPSocket::Close() {
	closesocket(sock);
	sock = INVALID_SOCKET;
}

//TODO: auto-close a disconnected server
int TCPSocket::Send(const void* data, int len, int flags) {
	if (sock == INVALID_SOCKET) {
		return 0;
	}
	int ret = send(sock, (const char*)data, len, flags);
	if (ret <= 0) {
		Close();
	}
	return ret;
}

int TCPSocket::Recv(void* data, int maxlen, int flags) {
	if (sock == INVALID_SOCKET) {
		return 0;
	}
	int ret = recv(sock, (char*)data, maxlen, flags);
	if (ret <= 0) {
		Close();
	}
	return ret;
}

/* TCPServerSocket definition
*/

TCPServerSocket::TCPServerSocket() {
	sock = INVALID_SOCKET;
}

TCPServerSocket::TCPServerSocket(int port) {
	Open(port);
}

TCPServerSocket::~TCPServerSocket() {
	Close();
}

int TCPServerSocket::Open(int port) {
	addrinfo *ptr = nullptr, hints;
	char buf[100];
	sprintf(buf, "%d",port); //std compliant itoa()

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(nullptr, buf, &hints, &ptr)) {
		return -1;
	}

	sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

	if (sock == INVALID_SOCKET) {
		freeaddrinfo(ptr);
		return -2;
	}

	if (bind(sock, ptr->ai_addr, ptr->ai_addrlen) == SOCKET_ERROR) {
		closesocket(sock);
		freeaddrinfo(ptr);
		return -3;
	}

	freeaddrinfo(ptr);

	return 0;
}

void TCPServerSocket::Close() {
	closesocket(sock);
}

int TCPServerSocket::Accept(TCPSocket* s, int uSeconds) {
	if (listen(sock, SOMAXCONN) == SOCKET_ERROR) {
		return -1;
	}

	//file descriptor sets are to prevent blocking
	fd_set readfds;
	timeval tv = {0, uSeconds};

	FD_ZERO(&readfds);
	FD_SET(sock, &readfds);

	select(0, &readfds, nullptr, nullptr, &tv);

	//I don't want this to block
	if (FD_ISSET(sock, &readfds)) {
		if ((s->sock = accept(sock, nullptr, nullptr)) == INVALID_SOCKET) {
			return -1;
		}
		return 1;
	}
	return 0;
}