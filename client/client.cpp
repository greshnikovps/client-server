#include "client.h"

Client::Client()
{
}

int Client::sendTxtFile(const std::string& fileName, const std::string& serverIP)
{
	std::ifstream fileStream(fileName);
	if (fileStream.fail()) {
		std::cout << "Can't open file " << fileName << std::endl;
		return -1;
	}
	std::stringstream buffer;
	buffer << fileStream.rdbuf();

	int socket = getSocketByIP(serverIP);
	if (socket != INVALID_SOCKET)
		send(socket, buffer.str().data(), buffer.str().size(), 0);
	else
		return -1;
	return 0;
}

int Client::getSocketByIP(const std::string& serverIP)
{
	int sock = 0;
	sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		std::cout << "Error socket creation" << std::endl;
		return INVALID_SOCKET;
	}
	if (inet_pton(AF_INET, serverIP.data(), &serv_addr.sin_addr) <= 0) {
		std::cout << "Invalid address " << serverIP << std::endl;
		return INVALID_SOCKET;
	}
	if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		std::cout << "Failure connection to server" << std::endl;
		return INVALID_SOCKET;
	}
	return sock;
}
