#include "server.hpp"

int Server::cmdPong(Client *aux, std::string tk)
{
    Client *cl = aux;
    cl->newMessage("PONG irc.telo.net " + tk);
    return 0;
}