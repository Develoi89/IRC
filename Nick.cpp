#include "server.hpp"

bool Server::existClientByNick(std::string name){
    std::map<int, Client *>::iterator it = map_clients.begin();
    while(it != map_clients.end()){
        if((*it).second->getNick() == name){
            return true;
        }
        it++;
    }
    return false;
}

bool Server::nickAllow(std::string nick) {
   const std::string special = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890[]{}\\|-";

    for (std::size_t i = 0; i < nick.length(); ++i) {
        if (special.find(nick[i]) != std::string::npos) {
            return true;
        }
    }

    return false;
}

void Server::cmdNick(Client *aux, std::vector<std::string>tokens){
    if(tokens.size() < 2){
        aux->newMessage(std::string("431 ") + " :No nickname given");
        return ;
    }
    if(existClientByNick(tokens[1])){
        aux->newMessage(std::string("433 ") + aux->getUser() + " " + tokens[1] + " :Nickname is already in use");
        return ;
    }
    if(nickAllow(tokens[1]) == false){
        aux->newMessage(std::string("432 ") + aux->getUser() + " " + tokens[1] + " :Erroneus nickname");
        return ;
    }

    aux->setNick(tokens[1]);
}