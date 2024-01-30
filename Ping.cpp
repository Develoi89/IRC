#include "server.hpp"
int Server::cmdPing(Client *aux, std::vector<std::string> tokens)
{
    Server::cmdPong(aux, tokens[1]);
    return 0;
}