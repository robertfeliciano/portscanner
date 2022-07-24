#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <unordered_map>
#include <thread>
#include <iostream>
#include <iomanip>
#include <mutex>
#include <vector>

using std::cout;
using std::endl;
using std::unordered_map;
using std::string;
using std::thread;
using std::mutex;
using std::lock_guard;
using std::vector;

struct port_args {
    int start;
    int end;
    int sockfd;
    struct sockaddr_in* tower;
};

static bool verbose = false;

static unordered_map<int, string> ports = {
    {631, "This port is used for printer driver software so it is usually always on."},
};

vector<int> open_ports;
static int arr_index = 0;

//i kind of wanted to use an atomic<int> for arr_index but since 
// i'd have to use a mutex for the array anyway i decided not to

static mutex tower_socket_mtx;