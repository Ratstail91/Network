#include "network.hpp"

#include <stdexcept>

void NetworkInit() {
	WSADATA wsaData;   // if this doesn't work
	//WSAData wsaData; // then try this instead

	// MAKEWORD(1,1) for Winsock 1.1, MAKEWORD(2,0) for Winsock 2.0:

	if (WSAStartup(MAKEWORD(2,0), &wsaData) != 0) {
		throw(std::runtime_error("WSAStartup failed"));
	}
}

void NetworkQuit() {
	WSACleanup();
}
