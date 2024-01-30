#include "server.hpp"
#include "Channel.hpp"

int Server::cmdJoin(Client *aux, std::vector<std::string> tokens) //Change the channel’s mode:
{
    std::vector<std::string> ch;
    std::vector<std::string> ps;

    std::string key = tokens[1];

    std::map<std::string, Channel>::iterator iter = _channels.find(key);
    if (iter != _channels.end())
    {
        iter->second.getClist().push_back(*aux);
    }
    else
    {
        Channel first(key, *aux);
        _channels[key] = first;
    }
    return 0;
}