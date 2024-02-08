#include "server.hpp"

int Server::cmdKick(Client *aux, std::vector<std::string> tokens) //Eject a client from the channel
{
    std::cout << "KICK called" << std::endl;
    std::string key = tokens[1];
    std::map<std::string, Channel>::iterator iter = _channels.find(key);
    if (iter != _channels.end())
    {
        const std::set<int>& opera = iter->second.getOps();
        for (std::set<int>::const_iterator is = opera.begin(); is != opera.end(); ++is)
            if(aux->getFd() == *is){
                const std::set<int>& mem = iter->second.getMem();
                for (std::set<int>::const_iterator it = mem.begin(); is != mem.end(); ++it)
                    
            }
    }
    else
        aux->newMessage("403 " + aux->getNick() + key + " :No such channel");
    return 0;
}