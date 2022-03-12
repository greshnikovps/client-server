#pragma once
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>
#include <stdio.h>
#include <syslog.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>

#define RECEIVE_TIMEOUT_USEC 10
#define PORT 8080

class Server {
public:
	Server();
	int recvAndSaveFile(std::string fileName);
private:
	int setReceiveTimeout(int usec);
	int ReceiveMessage(char* dst, size_t msgSize);
	int ReceiveMessageSize(size_t& msgSize);

	sockaddr_in addr;
	int recvSocket;
	int acceptSocket;
	bool acceptRequired;
};