/* a multithreaded C program to check for open ports on Linux machines. */

#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

void help(){
    printf("Please specify a flag:\n"
    "  '-s' - Scan system ports\n"
    "  '-u' - Scan user ports\n"
    "  '-p' - Scan private ports\n"
    "  '-a' - Scan all ports\n"
    "  '-h' - Display this help message\n");
}

void init_threads(int flag){
    int start, end;
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
    struct hostent* server = gethostbyname("localhost");
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    bcopy((char*) server->h_addr,
          (char*) &server_addr.sin_addr.s_addr,
          server->h_length);

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