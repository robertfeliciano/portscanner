
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX_THREADS 4

struct port_args {
    int start;
    int end;
    int sockfd;
    struct sockaddr_in* tower;
};

