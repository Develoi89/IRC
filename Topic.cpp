#include "server.hpp"
#include "Channel.hpp"

int Server::cmdTopic(Client *aux, std::vector<std::string> tokens) //Change or view the channel topic
{
     if(tokens.size() < 2){
        aux->newMessage(std::string("461 ") + aux->getNick() + " " + tokens[0] + ":Not enough parameters");
        return 0;
    }

    int exists = findChannelByName(tokens[1]);

	if (exists == 0)
	{
		aux->newMessage(std::string("403 ") +  aux->getNick() + " " + tokens[1] + " :No such channel");
        return 0;
	}
    Channel *ch = &_channels[tokens[1]];

    if (!ch->isMember(aux->getFd())) {
        aux->newMessage(std::string("442 ") +  aux->getNick() + " " + tokens[1] + " :You're not on that channel");
        return 0;
    }
    if (tokens.size() > 2 && ch->getMode('t') && !ch->isOps(aux->getFd()))
	{
		aux->newMessage(std::string("482 ") + aux->getNick() + " " + tokens[1] + " :You're not channel operator");
        return 0;
	}

    if (tokens.size() > 2 && tokens[2] == ":")
	{
		ch->setTopic("");
		std::string msg = "TOPIC " + ch->getName() + " :" + ch->getTopic();
        const std::set<int>& _members = ch->getMem();  
        for (std::set<int>::const_iterator it = _members.begin(); it != _members.end(); ++it) {
            map_clients[*it]->newMessage(msg);
        }
        return 0;
	}
	if (tokens.size() > 2)
	{
		std::string message = tokens[2];
		for (unsigned long i = 3; i < tokens.size(); i++)
			message.append(" " + tokens[i]);
		ch->setTopic(message);
        const std::set<int>& _members = ch->getMem();  
        for (std::set<int>::const_iterator it = _members.begin(); it != _members.end(); ++it) {
            map_clients[*it]->newMessage(std::string("332 ") + aux->getNick() + " " + ch->getName() + " " + ch->getTopic());
            map_clients[*it]->newMessage(std::string("333 ") + aux->getNick() + " " + ch->getName() + " " + ch->getTopic() + " " + _currentTime());
        }
        return 0;
	}else{
        if(ch->getTopic() != ""){
            aux->newMessage(std::string("332 ") + aux->getNick() + " " + ch->getName() + " " + ch->getTopic());
            aux->newMessage(std::string("333 ") + aux->getNick() + " " + ch->getName() + " " + ch->getTopic() + " " + _currentTime());
        }else{
            aux->newMessage(std::string("331 ") + aux->getNick() + " " + ch->getName() + " :No topic is set");
        }
    }
    return 0;

}