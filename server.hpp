#ifndef SERVER_HPP
#define SERVER_HPP
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

class Server{
    public:
        Server(int port, std::string password);
    private:
        std::string password;
        int port;
        struct pollfd serverfd_;
        std::vector<pollfd>(1) pollfd_; 

    
};
#endif