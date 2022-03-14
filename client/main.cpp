#include "client.h"
#include <iostream>

int main(int argc, char* argv[]){
    if (argc != 3) {
        std::cout << "Wrong agrs!" << std::endl;
        return -1;
    }
    std::string fileName(argv[1]);
    std::string serverIP(argv[2]);
    Client client;
    if (client.sendTxtFile(fileName, serverIP) != -1)
        std::cout << "Sent successfully" << std::endl;
    else
        std::cout << "Some error occured" << std::endl;
    return 0;
}
