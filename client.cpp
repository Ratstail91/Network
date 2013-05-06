#include "network.hpp"

#include <exception>
#include <iostream>
#include <string>

using namespace std;

int main(int, char**) {
	NetworkInit();

	int ret = 0;
	TCPSocket sock;
	if ((ret = sock.Open("127.0.0.1", 2000)) != 0) {
		cerr << "Failed to open the client socket: " << ret << endl;
		return 1;
	}
	string input;

	int connected = 1;
	cout << "Client active" << endl;
	while (connected > 0) {
		getline(cin, input);

		if (input.length() == 0) {
			continue; //prevent empty messages
		}

		ret = sock.Send(input.c_str(), input.length());

		if (ret <= 0) {
			continue;
		}
		else if (ret != input.length()) {
			cerr << "Warning: not all data was sent" << endl;
		}

		if (input == "quit") {
			connected = 0;
		}
	}

	sock.Close();

	NetworkQuit();
	return 0;
}