/* a multithreaded C program to check for open ports on Linux machines. 
   i think it should also work on macOS and BSD systems if compiled with g++ for the thread library */

#include "pscan.hpp"

void help(){
    printf("Please specify a flag:\n"
    "  '-s' - Scan system ports\n"
    "  '-u' - Scan user ports\n"
    "  '-p' - Scan private ports\n"
    "  '-a' - Scan all ports\n"
    "  '-h' - Display this help message\n");
}

void count_open_ports(int start, int end){
    int sockfd;
    struct sockaddr_in tower;

    //localhost is 127.0.0.1 (hopefully)
    if (inet_pton(AF_INET, "127.0.0.1", &tower.sin_addr) < 1){
        fprintf(stderr, "Problem loading your IP address\n");
        exit(EXIT_FAILURE);
    }
    memset(&tower, 0, sizeof(tower));
    tower.sin_family = AF_INET;
    tower.sin_addr.s_addr = inet_addr("127.0.0.1");

    for (int port_num = start; port_num <= end; port_num++){
        tower.sin_port = htons(port_num);
        if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0){
            fprintf(stderr, "Error: Failed to create socket.\nPlease try again\n");
            close(sockfd);
            port_num--;
            continue;
        }
        if (connect(sockfd, (struct sockaddr*) &tower, sizeof(tower)) == 0){
            //cout << std::setw(11);
            lock_guard<mutex> guard(vec_mtx);
            open_ports.push_back(port_num);
        }
        close(sockfd);
    }
}

void verbose_printer(char flag){
    return;
}

void thread_handler(int start, int end, char flag){
    int max_threads = thread::hardware_concurrency();
    thread thread_list[max_threads];
    int interval_size = (end - start + 1)/max_threads;
    int thread_num = 0;

    //create all the threads
    for (; thread_num < max_threads; thread_num++){
        int right_bound = start + interval_size;
        thread_list[thread_num] = thread(count_open_ports, start, right_bound);
        start = right_bound + 1;
    }
    //round up all the threads
    for (thread_num = 0; thread_num < max_threads; thread_num++){
        thread_list[thread_num].join();
    }

    for (int port : open_ports){
        cout << "port " << port << " is open\n";
    }

    if (verbose){
        verbose_printer(flag);
    }
    
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
    int c, start, end;

    while((c = getopt(argc, argv, "vsupah")) != -1){
        switch (c){
            case 'v':
                verbose = true;
            case 's':
                start = 0;
                end = 1023;
                thread_handler(start, end, (char) c);
                break;
            case 'u':
                start = 1024;
                end = 49151;
                thread_handler(start, end, (char) c);
                break;
            case 'p':
                start = 49152;
                end = 65535;
                thread_handler(start, end, (char) c);
                break;
            case 'a':
                start = 0;
                end = 65535;
                thread_handler(start, end, (char) c);
                break;
            case 'h':
            default:
                help();
                return 1;
        }
    }
    return 0;
}