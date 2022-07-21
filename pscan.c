/* a multithreaded C program to check for open ports on Linux machines. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void help(){
    printf("Please specify a flag:\n"
    "  '-s' - Scan system ports\n"
    "  '-u' - Scan user ports\n"
    "  '-p' - Scan private ports\n"
    "  '-a' - Scan all ports\n"
    "  '-h' - Display this help message\n");
}

void init_threads(int flag){
    int start, end, sockfd;
    struct sockaddr_in tower;
    socklen_t addr_size = sizeof(struct sockaddr_in);
    switch(flag){
        case 's':
            start = 0;
            end = 1023;
            break;
        case 'u':
            start = 1024;
            end = 49151;
            break;
        case 'p':
            start = 49152;
            end = 65535;
            break;
        case 'a':
            start = 0;
            end = 65535;
            break;
    }
    //printf("start: %d\nend: %d\n", start, end);
    //localhost is 127.0.0.1
    if (inet_pton(AF_INET, "127.0.0.1", &tower.sin_addr) < 1){
        fprintf(stderr, "Problem loading your IP address\n");
        exit(EXIT_FAILURE);
    }
    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0){
        fprintf(stderr, "Error: Failed to create socket.\nPlease try again\n");
        exit(EXIT_FAILURE);
    }
    memset(&tower, 0, sizeof(tower));
    tower.sin_family = AF_INET;
    tower.sin_port = htons(25555);
    tower.sin_addr.s_addr = inet_addr("127.0.0.1");


    if (connect(sockfd, (struct sockaddr*) &tower, sizeof(tower)) < 0){
        fprintf(stderr, "port is closed\n");
    }
    else{
        printf("port is open\n");
    }
    close(sockfd);
}

int main(int argc, char* argv[]){
    if (argc == 1){
        help();
        return 1;
    }
    char flag;
    int c;

    while((c = getopt(argc, argv, "supah")) != -1){
        switch (c){
            case 's':
                flag = c;
                break;
            case 'u':
                flag = c;
                break;
            case 'p':
                flag = c;
                break;
            case 'a':
                flag = c;
                break;
            case 'h':
            case '?':
            default:
                help();
                return 1;
        }
    }
    init_threads(flag);
    return 0;
}