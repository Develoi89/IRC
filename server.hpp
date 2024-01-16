#ifndef SERVER_HPP
#define SERVER_HPP
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <poll.h>
#include <csignal>
#include <map>
#include "Client.hpp"



#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
class Client;

class Server{
    public:
        Server(int port, std::string password);
        void loop();
    private:
        std::string password;
        int port;
        std::map<int, Client *>map_clients;

        struct pollfd serverfd_;
        std::vector<pollfd> _pollsfd;
    
};
#endif