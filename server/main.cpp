#include "server.h"
#include <dirent.h>
#include <iterator>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <syslog.h>
#include <unistd.h>
#include <vector>
#include <csignal>

#define FILE_NAME "receivedFile.txt"

void signalHandler(int signum) {
    exit(EXIT_SUCCESS);
}

int main(void)
{
    pid_t pid, sid;

    pid = fork();
    if (pid > 0)
        exit(EXIT_SUCCESS);
    else if (pid < 0)
        exit(EXIT_FAILURE);

    umask(0);

    sid = setsid();
    if (sid < 0)
        exit(EXIT_FAILURE);

    signal(SIGTERM, signalHandler);
    signal(SIGHUP, signalHandler);

    const int SLEEP_INTERVAL = 1;

    Server server;
    while (1)
    {
        server.recvAndSaveFile(FILE_NAME);
        sleep(SLEEP_INTERVAL);
    }
    exit(EXIT_SUCCESS);
}