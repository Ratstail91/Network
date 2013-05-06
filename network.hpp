#ifndef NETWORK_HPP_
#define NETWORK_HPP_

/* Unless noted otherwise, functions return 0 on success, or a negative
 * value on error. There are NO blocking functions.
 * 
 * This is my idea for a minimalist networking interface. This is what I
 * /wish/ existed. I might try and make this work, but I'm inexperienced
 * with networking and making APIs.
*/

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
	 * return:
	 *     0: clean exit
	 *     -1: getaddrinfo() failed (did you forget NetworkInit()?)
	 *     -2: socket() failed
	 *     -3: connect() failed
	*/
	int Open(const char* ip, int port);
	void Close();

	/* Send() and Receive()
	 * param 1: data to be sent/received
	 * param 2: length/maxlength of the data
	 * param 3: flags to the internal function
	 * return:
	 *     >0: the amount of data sent/received (not necessarily the same value as len/maxlen)
	 *     0: the local and remote socket pair has been closed
	 *     SOCKET_ERROR: unknown socket error
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

	/* param 1: port to open the server socket on
	 * return:
	 *     0: clean exit
	 *     -1: getaddrinfo() failed (did you forget NetworkInit()?)
	 *     -2: socket() failed
	 *     -3: bind() failed
	*/
	int Open(int port);
	void Close();

	/* param 1: pointer to a socket to be created.
	 * return:
	 *     1: New connection, socket can be used normally
	 *     0: No new connection, socket is not altered
	 *     -1: Unknown error
	*/
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
