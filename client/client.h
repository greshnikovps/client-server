#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#define PORT 8080

class Client {
public:
	Client();
	int sendTxtFile(const std::string& fileName, const std::string& serverIP);
private:
	int getSocketByIP(const std::string& serverIP);
};