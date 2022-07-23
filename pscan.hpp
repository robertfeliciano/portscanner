
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <unordered_map>
#include <iostream>

#define MAX_THREADS 4

struct port_args {
    int start;
    int end;
    int sockfd;
    struct sockaddr_in* tower;
};

std::unordered_map<int, std::string> ports = {
    {631, "This port is used for printer driver software so it is usually always on."},
};