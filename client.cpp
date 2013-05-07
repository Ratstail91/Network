#include "network.hpp"

#include <exception>
#include <iostream>
#include <string>

using namespace std;

int main(int, char**) {
	cout << "Client running" << endl;
	try {
		NetworkInit();
		TCPSocket sock("127.0.0.1", 2000);
		string input;
		bool running = true;
		while(running) {
			getline(cin, input);
			if (input.length() <= 0) {
				continue;
			}
			if (sock.Send(input.c_str(), input.length()) != input.length()) {
				cerr << "Warning: not all data was sent" << endl;
			}
			if (input == "quit") {
				running = false;
			}
		}
		sock.Close();
		NetworkQuit();
	}
	catch(exception& e) {
		cerr << "Error: " << e.what() << endl;
		return 1;
	}
	return 0;
}