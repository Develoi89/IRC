#include "server.hpp"

int Server::searchByFd(std::string target){
    for (std::map<int, Client*>::iterator it = map_clients.begin(); it != map_clients.end(); ++it){
        Client *aux = it->second;
        if(target == aux->getNick()){

            return it->first;
        }
    }
    return 0;
}

int Server::cmdPrivmsg(Client *aux, std::vector<std::string> tokens)
{
    for(int i = 0; i < tokens.size(); i++){
        std::cout << tokens[i] << std::endl;
    }
    std::string target_name = tokens[1];
    std::string msg = "";
    int fd_target = searchByFd(target_name);
    Client *new_cl = map_clients[fd_target];
    if(fd_target != 0){
        if(tokens[2][0] != ':')
            tokens[2] = ":" + tokens[2];
        msg = ":" + aux->getNick() + "!" + aux->getNick() + "@127.0.0.1 PRIVMSG " + new_cl->getNick();
        for(long i = 2; i < tokens.size(); i++){
            msg.append(" " + tokens[i]);
        }
        new_cl->newMessage(msg);
    }
    else{
        std::cout << "no existe este usuario" << std::endl;
    }
    return 0;   

}
