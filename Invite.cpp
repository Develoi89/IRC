#include "server.hpp"

Client *Server::findClientByNick(std::string name){
    std::map<int, Client*>::iterator it;

    for (it = map_clients.begin(); it != map_clients.end(); ++it) {
        if (it->second->getNick() == name) {
            return it->second; 
            break;
        }
    }
    return nullptr;
}


int Server::cmdInvite(Client *aux, std::vector<std::string> tokens) //Invite a client to a channel
{
    if(tokens.size() < 3){
        aux->newMessage(std::string("461 ") + aux->getNick() + " " + tokens[0] + ":Not enough parameters");
        return 0;
    }
    Client *cl = findClientByNick(tokens[1]);

    int exists = findChannelByName(tokens[2]);
	if (exists == 0)
	{
		aux->newMessage(std::string("403 ") +  aux->getNick() + " " + tokens[2] + " :No such channel");
        return 0;
	}
    Channel *ch = &_channels[tokens[2]];
    if (!ch->isMember(aux->getFd())) {
        aux->newMessage(std::string("442 ") +  aux->getNick() + " " + tokens[2] + " :You're not on that channel");
        return 0;
    }
    // if (!ch->isOps(aux->getFd()))
	// {
	// 	aux->newMessage(std::string("482 ") + aux->getNick() + " " + tokens[1] + " :You're not channel operator");
    //     return 0;
	// }

    cl->newMessage(":" + aux->getNick() + " INVITE " + cl->getNick() + " " + tokens[2]);
    aux->newMessage(std::string("341 ") + aux->getNick() + " " + cl->getNick() + " " + tokens[2]);
    return 0;
}

