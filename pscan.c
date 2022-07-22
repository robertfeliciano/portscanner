/* a multithreaded C program to check for open ports on Linux machines. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

struct port_args {
    int start;
    int end;
    int sockfd;
    struct sockaddr_in* tower;
};

void help(){
    printf("Please specify a flag:\n"
    "  '-s' - Scan system ports\n"
    "  '-u' - Scan user ports\n"
    "  '-p' - Scan private ports\n"
    "  '-a' - Scan all ports\n"
    "  '-h' - Display this help message\n");
}

void* count_open_ports(void* args){
    struct port_args* pa = args;
    int start = pa->start;
    int end = pa->end;
    int sockfd = pa->sockfd;
    struct sockaddr_in* tower = pa->tower;
    printf("start: %d\n", start);
    pthread_exit(NULL);
}

void init_threads(int flag){
    int start, end, sockfd;
    struct sockaddr_in tower;
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
    memset(&tower, 0, sizeof(tower));
    tower.sin_family = AF_INET;
    tower.sin_addr.s_addr = inet_addr("127.0.0.1");

    for (int i = start; i <= end; i++){
        if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0){
            fprintf(stderr, "Error: Failed to create socket.\nPlease try again\n");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
        tower.sin_port = htons(i);
        if (connect(sockfd, (struct sockaddr*) &tower, sizeof(tower)) < 0){
            //fprintf(stderr, "port %d is closed\n", i);
        }
        else{
            printf("port %d is open\n", i);
        }
        close(sockfd);
    }
    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0){
            fprintf(stderr, "Error: Failed to create socket.\nPlease try again\n");
            exit(EXIT_FAILURE);
    }
    tower.sin_port = htons(65535);
    printf("\n\n\n\n\n\n");
    if (connect(sockfd, (struct sockaddr*) &tower, sizeof(tower)) < 0){
            fprintf(stderr, "port %d is closed\n", start);
    }
    else{
        printf("port %d is open\n", start);
    }
    close(sockfd);

    /* pthread_t p = 0;
    struct port_args* pa;
    memset(pa, 0, sizeof(*pa));
    pa->start = start;
    pa->end = end;
    pa->tower = &tower;
    pa->sockfd = sockfd;
    pthread_create(&p, NULL, count_open_ports, (void*) pa);
    close(sockfd); */
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