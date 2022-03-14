#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>

#define PORT 8080
#define INVALID_SOCKET -1

class Client {
public:
    Client();
    int sendTxtFile(const std::string& fileName, const std::string& serverIP);
private:
    int getSocketByIP(const std::string& serverIP);
};
