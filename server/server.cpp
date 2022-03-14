#include "server.h"

using namespace std;

Server::Server()
{
    acceptSocket = socket(AF_INET, SOCK_STREAM, 0);
    recvSocket = INVALID_SOCKET;

    char host[256];
    struct hostent* host_entry;
    gethostname(host, sizeof(host));
    host_entry = gethostbyname(host);
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);
    addr.sin_family = AF_INET;
    bind(acceptSocket, (struct sockaddr*)&addr, sizeof(addr));
    listen(acceptSocket, SOMAXCONN);
    acceptRequired = true;

    int flags = fcntl(acceptSocket, F_GETFL);
    fcntl(acceptSocket, F_SETFL, flags | O_NONBLOCK);
}

int Server::recvAndSaveFile(std::string fileName)
{
    size_t msgSize = 0;
    if (ReceiveMessageSize(msgSize) != -1 && msgSize != 0) {
        char* buf = new char[msgSize];
        if (ReceiveMessage(buf, msgSize) != -1) {
            ofstream outputFile(fileName);
            if (!outputFile) {
                delete[] buf;
                return -1;
            }
            outputFile.write(buf, msgSize);
            outputFile.close();
        }
        else {
            delete[] buf;
            return -1;
        }
        delete[] buf;
        return 0;
    }
    return -1;
}

int Server::ReceiveMessageSize(size_t& msgSize) {
    if (acceptRequired) {
        socklen_t addrLen = sizeof(addr);
        recvSocket = accept(acceptSocket, (struct sockaddr*)&addr, &addrLen);
        if (recvSocket < 0) {
            return -1;
        }
        acceptRequired = false;
        int flags = fcntl(recvSocket, F_GETFL);
        fcntl(recvSocket, F_SETFL, flags | O_NONBLOCK);
    }
    if (recv(recvSocket, reinterpret_cast<char*>(&msgSize), sizeof(msgSize), 0) <= 0) {
        return -1;
    }
    return 0;
}

int Server::ReceiveMessage(char* dst, size_t msgSize) {
    if (msgSize <= 0)
        return -1;

    int result = 0, iter = 0;
    size_t recvSize = 0;

    while (msgSize > 0) {
        recvSize = (msgSize < 1024) ? msgSize : 1024;
        result = recv(recvSocket, dst + iter, recvSize, 0);
        if (result < 0) {
            result = -1;
            break;
        }
        msgSize = msgSize - result;
        iter = iter + result;
    }
    if (result < 0)
        return -1;

    return 0;
}
