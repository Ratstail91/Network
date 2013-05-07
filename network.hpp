#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <cstdint>

#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x501
#include <winsock2.h>
#include <ws2tcpip.h>

void NetworkInit();
void NetworkQuit();

class TCPSocket {
public:
	TCPSocket();
	TCPSocket(const char* ip, int port);
	~TCPSocket();

	/* param 1: ip address to connect to
	 * param 2: port to open the server socket on
	*/
	void Open(const char* ip, int port);
	void Close();

	/* Send() and Receive()
	 * param 1: data to be sent/received
	 * param 2: length/maxlength of the data
	 * param 3: flags to the internal function
	 * return:
	 *     the amount of data sent/received (not necessarily the same value as len/maxlen)
	*/
	int Send(const void* data, int len, int flags = 0);
	int Recv(void* data, int maxlen, int flags = 0);
private:
	SOCKET sock;
	friend class TCPServerSocket;
};

class TCPServerSocket {
public:
	TCPServerSocket();
	TCPServerSocket(int port);
	~TCPServerSocket();

	void Open(int port);
	void Close();

	int Accept(TCPSocket*, int uSeconds = 0);
private:
	SOCKET sock;
};
/*
class UDPPacket {
public:
	UDPPacket();
	UDPPacket(int size);
	~UDPPacket();

	int Alloc(int size);
	int Resize(int size);
	int Free();

	int GetSize() const;
	void* GetDataPtr() const;

	int SetIPAddress(const char* host, int port);
	//?
private:
	int size;
	void* data;
};

class UDPSocket {
public:
	UDPSocket();
	UDPSocket(int port);
	~UDPSocket();

	int Open(int port);
	void Close();

	int Send(UDPPacket*);
	int Recv(UDPPacket*);

	int GetPort() const;
private:
	SOCKET sock;
};
*/
#endif
