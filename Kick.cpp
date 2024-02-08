#include "server.hpp"

int Server::cmdKick(Client *aux, std::vector<std::string> tokens) //Eject a client from the channel
{
    std::cout << "KICK called" << std::endl;
    std::string key = tokens[1];
    std::map<std::string, Channel>::iterator iter = _channels.find(key);
    if (iter != _channels.end())
    {
        if (iter->second.isOps(aux->getFd()))
        {
            std::map<int, Client*>::iterator it;
            for (it = map_clients.begin(); it != map_clients.end(); it++)
            {
                if(it->second->getNick() == tokens[2])
                {
                    if(iter->second.isMember(it->second->getFd()))
                    {
                        iter->second.deleteMem(it->second->getFd());
                        it->second->newMessage("You kicked of " + iter->second.getName() + " channel.");
                        iter->second.deleteClient(it->second->getFd());
                        if(iter->second.isOps(it->second->getFd()))
                            iter->second.deleteOp(it->second->getFd());
                    }
                    else
                    {
                        aux->newMessage("441 " + aux->getNick() + tokens[2] + key + " :They aren't on that channel");
                        return 0;
                    }
                }
            }   
        }
        else
            aux->newMessage("482 " + aux->getNick() + key + " :You're not channel operator");       
    }
    else
        aux->newMessage("403 " + aux->getNick() + key + " :No such channel");
    return 0;
}