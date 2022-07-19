/* a multithreaded C program to check for open ports on Linux machines. */

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

void system_ports(){
    printf("Checking system ports...\n");
    short start = 0, end = 1023;
}

void user_ports(){
    printf("Checking user ports...\n");
    short start = 1024, end = 49151;
}

void private_ports(){
    printf("Checking private ports...\n");
    short start = 49152, end = 65535;
}

void all_ports(){
    printf("Checking all ports...\n");
    short start = 0, end = 65535;
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
                system_ports();
                break;
            case 'u':
                user_ports();
                break;
            case 'p':
                private_ports();
                break;
            case 'a':
                all_ports();
                break;
            case 'h':
            case '?':
            default:
                help();
                return 1;
        }
    }

}