#include "network.hpp"

#include <exception>
#include <iostream>
#include <cstring>

using namespace std;

#define BUFSIZE 512

int main(int, char**) {
	cout << "Server running" << endl;
	try {
		NetworkInit();
		TCPServerSocket serv(2000);
		TCPSocket sock;
		while(serv.Accept(&sock) <= 0); //call this forever
		char buffer[BUFSIZE];
		bool running = true;
		while(running) {
			memset(buffer, 0, BUFSIZE); //zero the buffer
			if (sock.Recv(buffer, BUFSIZE) <= 0) {
				continue;
			}
			cout << buffer << endl;
			if (!strcmp(buffer, "quit")) {
				running = false;
			}
		}
		sock.Close();
		serv.Close();
		NetworkQuit();
	}
	catch(exception& e) {
		cerr << "Error: " << e.what() << endl;
		return 1;
	}
	return 0;
}
