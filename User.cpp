#include "server.hpp"

bool Server::existClientByUser(std::string name){
    std::map<int, Client *>::iterator it = map_clients.begin();
    while(it != map_clients.end()){
        if((*it).second->getUser() == name){
            return true;
        }
        it++;
    }
    return false;
}


void Server::cmdUser(Client *aux, std::vector<std::string> tokens){
    if(aux->getNick() == "")
        return ;
	if (tokens.size() < 5){
        aux->newMessage(std::string("461 ") + aux->getNick() + " " + tokens[0] + std::string(" :Not enough parameters"));
		return ;
    }

    if(aux->getRg() == true || existClientByUser(tokens[1])){
        aux->newMessage(std::string("462 ") + aux->getNick() + " :You may not reregister");
        return ;
    }
    aux->setRg(true);
    aux->setUser(tokens[1]);
    aux->setName(tokens[4]);
    registerMsg(*aux);
}