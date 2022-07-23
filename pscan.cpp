/* a multithreaded C program to check for open ports on Linux machines. */
#include "pscan.h"

using namespace std;

void help(){
    printf("Please specify a flag:\n"
    "  '-s' - Scan system ports\n"
    "  '-u' - Scan user ports\n"
    "  '-p' - Scan private ports\n"
    "  '-a' - Scan all ports\n"
    "  '-h' - Display this help message\n");
}

void* count_open_ports(void* args){
    struct port_args* pa = (struct port_args*) args;
    int start = pa->start;
    int end = pa->end;
    int sockfd = pa->sockfd;
    struct sockaddr_in* tower = pa->tower;
    puts("\0");
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
    //localhost is 127.0.0.1 (hopefully)
    if (inet_pton(AF_INET, "127.0.0.1", &tower.sin_addr) < 1){
        fprintf(stderr, "Problem loading your IP address\n");
        exit(EXIT_FAILURE);
    }
    memset(&tower, 0, sizeof(tower));
    tower.sin_family = AF_INET;
    tower.sin_addr.s_addr = inet_addr("127.0.0.1");

    for (int i = start; i <= end; i++){
        tower.sin_port = htons(i);
        if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0){
            fprintf(stderr, "Error: Failed to create socket.\nPlease try again\n");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
        if (connect(sockfd, (struct sockaddr*) &tower, sizeof(tower)) == 0){
            printf("port %d is open\n", i);
        }
        close(sockfd);
    }
    pthread_t p = 0;
    struct port_args pa;
    memset(&pa, 0, sizeof(pa));
    pa.start = start;
    pa.end = end;
    pa.tower = &tower;
    pa.sockfd = sockfd;
    pthread_create(&p, NULL, count_open_ports, (void*) &pa);
    close(sockfd);
}

int main(int argc, char* argv[]){
    if (argc == 1){
        help();
        return 1;
    }
    if (strcmp(argv[1], "-") == 0){
        printf("I think you made a typo.\n");
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