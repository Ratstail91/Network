#include "network.hpp"

#include <stdexcept>

UDPRemote::UDPRemote() {
	host = port = 0;
}

UDPRemote::UDPRemote(const char* ip, int p) {
	Set(ip, p);
}

void UDPRemote::Set(const char* ip, int p) {
	//TODO
}

UDPSocket::UDPSocket() {
	sock = INVALID_SOCKET;
}

UDPSocket::UDPSocket(int port) {
	Open(port);
}

UDPSocket::~UDPSocket() {
	Close();
}

int UDPSocket::Open(int port) {
	//TODO
}

void UDPSocket::Close() {
	//TODO
}

int UDPSocket::Send(const void* data, int len, UDPRemote* rem, int flags) {
	//
}

int UDPSocket::Recv(void* data, int maxlen, UDPRemote* rem, int flags) {
	//
}
