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
int Server::findChannelByName(std::string name){
    std::map<std::string, Channel>::iterator it = _channels.find(name);
    if (it != _channels.end()) {
        return 1;
    }else{
        return 0; 
    }
}

int Server::sendChannel(Client *aux, std::vector<std::string> tokens, std::string target){
    int exists = findChannelByName(target);
    if(exists == 0){
        aux->newMessage(std::string("403 ") +aux->getNick() + " " + target + " :No such channel");
        return 0;
    }
    if(tokens.size() < 3){
        aux->newMessage(std::string("412 ") + aux->getNick() + " :No text to send");
        return 0;
    }
    Channel *ch = &_channels[tokens[1]];
    if (!ch->isMember(aux->getFd())) {
        aux->newMessage(std::string("442 ") +  aux->getNick() + " " + tokens[2] + " :You're not on that channel");
        return 0;
    }

	std::string	msg = ":" + aux->getNick() + " PRIVMSG " + ch->getName();
	if (tokens[2][0] != ':')
		tokens[2] = ":" + tokens[2];
	for (long i = 2; i < tokens.size(); i++)
		msg.append(" " + tokens[i]);
    const std::set<int>& _members = ch->getMem();  
	for (std::set<int>::const_iterator it = _members.begin(); it != _members.end(); ++it) {
        if(map_clients[*it]->getName() != aux->getName()){
            map_clients[*it]->newMessage(msg);
        }
    }
    return 0;
}

int Server::sendUser(Client *aux, std::vector<std::string> tokens, std::string target)
{
    if(tokens.size() < 2 || target[0] == ':'){
        aux->newMessage(std::string("411 ") + aux->getNick() + " :No recipient given " + "PRIVMSG");
        return 0;
    }
    if(tokens.size() < 3){
        aux->newMessage(std::string("412 ") + aux->getNick() + " :No text to send");
        return 0;
    }
    if(existClientByNick(target) == false){
        aux->newMessage(std::string("401 ") + aux->getNick() + " " + target + " :No suck nick/channel");
        return 0;
    }
    std::string target_name = target;
    std::string msg = "";
    int fd_target = searchByFd(target_name);
    if(fd_target != 0){
        if(tokens[2][0] != ':')
            tokens[2] = ":" + tokens[2];
        Client *new_cl = map_clients[fd_target];
        msg = ":" + aux->getNick() + "!" + aux->getUser() + "@127.0.0.1 PRIVMSG " + new_cl->getNick();
        for(long i = 2; i < tokens.size(); i++){
            msg.append(" " + tokens[i]);
        }
        new_cl->newMessage(msg);
    }
    return 0;
}

int Server::cmdPrivmsg(Client *aux, std::vector<std::string> tokens)
{
    if(tokens.size() > 1){
        size_t comas = tokens[1].find(',');
        if (comas != std::string::npos){
            std::vector<std::string> _sending;
            std::istringstream tokenStream(tokens[1]);
            std::string token;

            while (std::getline(tokenStream, token, ',')) {
                _sending.push_back(token);
            }
			for (long i = 0; i < _sending.size(); i++)
			{		
				if (_sending[i][0] == '#' || _sending[i][0] == '&')
					sendChannel(aux, tokens, _sending[i]);
				else
					sendUser(aux, tokens, _sending[i]);
			}
        }
        else{
            if (tokens[1][0] == '#' || tokens[1][0] == '&')
				sendChannel(aux, tokens, tokens[1]);
			else
				sendUser(aux, tokens, tokens[1]);
        }
    }
    return 0;  
}
