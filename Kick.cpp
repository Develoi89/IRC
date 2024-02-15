#include "server.hpp"

int Server::cmdKick(Client *aux, std::vector<std::string> tokens) //Eject a client from the channel
{
    if(tokens.size() < 3){
        aux->newMessage(std::string("461 ") + aux->getNick() + " " + tokens[0] + ":Not enough parameters");
        return 0;
    }

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
                        if(tokens.size() == 3 ){
                            it->second->newMessage("You kicked of " + iter->second.getName() + " channel.");
                        }
                        if(tokens.size() > 3){
                            std::string msg = "";
                            if (tokens[3][0] != ':')
                                tokens[3] = ":" + tokens[3];
                            for (long i = 3; i < tokens.size(); i++)
                                msg.append(" " + tokens[i]);
                            it->second->newMessage("You kicked of " + iter->second.getName() + " channel for this reason" + msg);
                        }
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