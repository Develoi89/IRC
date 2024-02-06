#include "server.hpp"
#include "Channel.hpp"

void Server::respIrssi(Client *aux, Channel *ch)
{
	if(ch->getTopic() != ""){
		aux->newMessage(std::string("332 ") + aux->getNick() + " " + ch->getName() + " " + ch->getTopic());
		// std::cout << std::string("332 ") + aux->getNick() + " " + ch->getName() + " " + ch->getTopic() << std::endl;
		aux->newMessage(std::string("333 ") + aux->getNick() + " " + ch->getName() + " " + aux->getNick() + " " + _currentTime());
		// std::cout << std::string("333 ") + aux->getNick() + " " + ch->getName() + " " + aux->getNick() + " " + _currentTime() << std::endl;
	}else{
		aux->newMessage(std::string("331 ") + aux->getNick() + " " + ch->getName() + " :No topic is set");
	}

	std::string	intro = aux->getNick() + "!" + aux->getUser() + "@127.0.0.1" + " JOIN " + ch->getName();
		const std::set<int>& _members = ch->getMem();  

	for (std::set<int>::const_iterator it = _members.begin(); it != _members.end(); ++it) {
        map_clients[*it]->newMessage(intro);
    }
	aux->newMessage(std::string("353 ") + aux->getNick() + " = " + ch->getName() + " :" + ""+ "SegfaultBot.");
	const std::set<int>& members = ch->getMem();  
	for (std::set<int>::const_iterator it = members.begin(); it != members.end(); ++it)
    {
        std::string prefix = "";
		const std::set<int>& opera = ch->getOps();  
		for (std::set<int>::const_iterator is = opera.begin(); is != opera.end(); ++is)
		{
        if (*is == *it)
            prefix = "@";
		aux->newMessage(std::string("353 ") + aux->getNick() + " = " + ch->getName() + " :"  + prefix + map_clients[*it]->getNick());
		// std::cout << std::string("353 ") + aux->getNick() + " = " + ch->getName() + " :"  + prefix + aux->getNick() << std::endl;
		}
    }
    aux->newMessage(std::string("366 ") + aux->getNick() + " " + ch->getName() + " :End of /NAMES list");
	// std::cout << std::string("366 ") + aux->getName() + " " + ch->getName() + " :End of /NAMES list" << std::endl;
}

std::vector<std::string> splitByComa(std::string str)
{
    std::vector<std::string> final;
    int start = 0, end = 0;

	while(start < str.size())
	{
		start = str.find_first_not_of(',', end);
		if(start == std::string::npos)
			break;
		end = str.find_first_of(',', start);
		if(end == std::string::npos)
		{
			final.push_back(str.substr(start));
			break;;
		}
		else
			final.push_back(str.substr(start, end - start));
	}
	return final;
}

int Server::cmdJoin(Client *aux, std::vector<std::string> tokens) //Change the channel’s mode:
{
    if(tokens.size() < 2)
    {
        std::cout << "not enought arguments." << std::endl;
        return 0;
    }
    std::vector<std::string> ch;
	std::vector<std::string> ps;

    ch = splitByComa(tokens[1]);
	// for (std::vector<std::string>::iterator it = ch.begin(); it != ch.end(); it++)
	// {
	// 	if(it[0] != "#" && it[0] != "&")
	// 	{
	// 		it->erase();
	// 		aux->newMessage(std::string("476 ") + *it + " :Bad Channel Mask");
	// 	}
	// }
	
    if(tokens.size() > 2)
        ps = splitByComa(tokens[2]);

    int i = 0;
    while(i < ch.size())
    {
        std::string key = ch[i];

        std::map<std::string, Channel>::iterator iter = _channels.find(key);
		
        if (iter != _channels.end())
		{
			if (i >= ps.size() && iter->second.passSetted())
				std::cout << ch[i] << " need a pass." << std::endl;
			else if(i >= ps.size() && !iter->second.passSetted()){
				if(key[0] != 35 && key[0] != 38)
					aux->newMessage(std::string("476 ") + key + " :Bad Channel Mask");
				else
				{
				iter->second.getClist().push_back(*aux);
				iter->second.setMem(aux->getFd());
				respIrssi(aux, &iter->second);
				}
			}
			else if (i <= ps.size() && ps[i] == iter->second.getPass() && iter->second.passSetted()){
				if(key[0] != 35 && key[0] != 38)
					aux->newMessage(std::string("476 ") + key + " :Bad Channel Mask");
				else
				{
            	iter->second.getClist().push_back(*aux);
				iter->second.setMem(aux->getFd());
				respIrssi(aux, &iter->second);
				}
			}
			else if (i <= ps.size() && !iter->second.passSetted()){
				if(key[0] != 35 && key[0] != 38)
					aux->newMessage(std::string("476 ") + key + " :Bad Channel Mask");
				else
				{
				iter->second.getClist().push_back(*aux);
				iter->second.setMem(aux->getFd());
				respIrssi(aux, &iter->second);
				}
			}
			else
				std::cout << "wrong pass." << std::endl;
		}
        else
        {
            Channel first(key, *aux);
			if(key[0] != 35 && key[0] != 38)
					aux->newMessage(std::string("476 ") + key + " :Bad Channel Mask");
			else
			{
			if (i < ps.size())
			{
				first.setPass(ps[i]);
				std::cout << first.getPass() << " as pass setted for " << key << " channel." << std::endl;
			}
			first.setOps(aux->getFd());
			first.setMem(aux->getFd());
			_channels[key] = first;
			respIrssi(aux, &first);
			}
        }
        i++;
    }

    return 0;
}