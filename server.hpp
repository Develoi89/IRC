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
#include "Utils.hpp"


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "Channel.hpp"
class Client;
class Channel;

class Server{
    private:
		std::map<std::string, Channel> _channels;
        std::string password;
        int port;
        int cls;
        std::map<int, Client *> map_clients;

        struct pollfd serverfd_;
        std::vector<pollfd> _pollsfd;
        Server();
    public:
        Server(int port, std::string password);

        void    _request(int i);
        void    loop();
        void    runCmd(std::vector<std::string> tkn, int i);
        void    _rmClient(const Client &c);
        bool    checkCmd(Client *aux, std::vector<std::string> tokens);
        int		cmdPing(Client *aux, std::vector<std::string> tokens);
		int		cmdPong(Client *aux, std::string tk);
		int		cmdJoin(Client *aux, std::vector<std::string> tokens);
		int		cmdMode(Client *aux, std::vector<std::string> tokens);
		void		cmdTopic(Client *aux, std::vector<std::string> tokens);
		int		cmdInvite(Client *aux, std::vector<std::string> tokens);
		int		cmdKick(Client *aux, std::vector<std::string> tokens);
        int     cmdPrivmsg(Client *aux, std::vector<std::string> tokens);
        int     searchByFd(std::string target);
        void    cmdUser(Client *aux, std::vector<std::string> tokens);
        void    cmdNick(Client *aux, std::vector<std::string>tokens);
        void    respIrssi(Client *aux, Channel *ch);
        bool    existClientByUser(std::string name);
        bool    existClientByNick(std::string nick);
        bool    nickAllow(std::string nick);
        int     sendChannel(Client *aux, std::vector<std::string> tokens, std::string target);
        int     sendUser(Client *aux, std::vector<std::string> tokens, std::string target);
        Channel     findChannelByName(std::string name);
        Client     *findClientByNick(std::string name);
        

        std::string _currentTime();

};
#endif