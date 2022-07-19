#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
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

int main(int argc, char* argv[]){
    if (argc == 1){
        help();
        return 1;
    }
    int flag;
    int c;

    while((c = getopt(argc, argv, "supah")) != -1){
        switch (c){
            case 's':
                flag = 1;
                printf("s\n");
                break;
            case 'u':
                flag = 2;
                printf("u\n");
                break;
            case 'p':
                flag = 3;
                printf("p\n");
                break;
            case 'a':
                flag = 4;
                printf("a\n");
                break;
            case 'h':
            case '?':
            default:
                help();
                return 1;
        }
    }
}