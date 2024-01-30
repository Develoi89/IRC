#include "server.hpp"

int Server::cmdKick(Client *aux, std::vector<std::string> tokens) //Eject a client from the channel
{
    std::cout << "KICK called" << std::endl;
    return 0;
}