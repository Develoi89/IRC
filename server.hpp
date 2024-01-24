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
        std::string password;
        int port;
        int cls;
        std::map<int, Client *>map_clients;

        struct pollfd serverfd_;
        std::vector<pollfd> _pollsfd;
        Server();
    public:
        Server(int port, std::string password);

        void    _request(int i);
        void    loop();
        void    runCmd(std::vector<std::string> tkn, int i);
        void    _rmClient(const Client &c);
};
#endif