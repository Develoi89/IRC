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


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

class Server{
    public:
        Server(int port, std::string password);
        void _request(int i);
        void loop();
        void runCmd(std::string buffer);
    private:
        std::string password;
        int port;


        struct pollfd serverfd_;
        std::vector<pollfd> _pollsfd;
    
};
#endif