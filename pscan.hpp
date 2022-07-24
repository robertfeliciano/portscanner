#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <unordered_map>
#include <thread>
#include <iostream>

#define MAX_THREADS 4

using std::cout;
using std::endl;
using std::unordered_map;
using std::string;
using std::thread;

struct port_args {
    int start;
    int end;
    int sockfd;
    struct sockaddr_in* tower;
};

unordered_map<int, string> ports = {
    {631, "This port is used for printer driver software so it is usually always on."},
};