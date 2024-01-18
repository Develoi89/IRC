#ifndef SERVER_HPP
#define SERVER_HPP
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <poll.h>
#include <string>
#include <sstream>
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
    private:
        std::string _password;
        int _port;
        std::map<int, Client *> _map_clients;
        struct pollfd _serverfd_;
        std::vector<pollfd> _pollsfd;

    public:
        Server(int port, std::string password);
        void _request(int i);
        void loop();
        void runCmd(std::string buffer, int i);  
        bool verifyPort(std::string port); 
};
#endif