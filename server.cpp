#include "network.hpp"

#include <exception>
#include <iostream>
#include <cstring>

using namespace std;

#define BUFSIZE 512

int main(int, char**) {
	NetworkInit();

	int ret = 0;
	TCPServerSocket server;
	if ((ret = server.Open(2000)) != 0) {
		cerr << "Failed to open the server socket: " << ret << endl;
		return 1;
	}

	TCPSocket sock;
//	ret = server.Accept(&sock, 10000000);
//	if (ret <= 0) {
//		cerr << "Failed to accept the client socket: " << ret << endl;
//		return 1;
//	}

	int connected = 0;
	while(connected <= 0) {
		if (server.Accept(&sock) > 0) {
			connected = 1;
		}
	}

	char buffer[BUFSIZE];
	memset(buffer,0,BUFSIZE);

	cout << "Server active" << endl;
	while(connected > 0) {
		memset(buffer, 0, BUFSIZE);
		if (sock.Recv(buffer, BUFSIZE) <= 0) {
			continue;
		}

		cout << buffer << endl;

		if (!strcmp(buffer, "quit")) {
			connected = 0;
		}
	}

	sock.Close();
	server.Close();

	NetworkQuit();
	return 0;
}