#include "server.hpp"

std::string mStr(Channel *c)
{
    std::string str = "+";
    if(c->getMode('i'))
        str += "i";
    if(c->getMode('t'))
        str += "t";
    if(c->getMode('k'))
        str += "k";
    if(c->getMode('l'))
        str += "l";
    return str;
}

int Server::cmdMode(Client *aux, std::vector<std::string> tokens) //Change the channel’s mode:
{
    if(tokens.size() < 2)
    {
        aux->newMessage("461 " + aux->getNick() + " MODE :Not enought arguments.");
        return 0;
    }
	else if (findChannelByName(tokens[1]) == 0)
	{
		aux->newMessage(std::string("403 ") +  aux->getNick() + " " + tokens[1] + " :No such channel");
        return 0;
	}
    else if (tokens.size() == 2)
    {
        std::string modeString = mStr(&_channels[tokens[1]]);
        aux->newMessage(std::string("324 ") +  aux->getNick() + " " + tokens[1] + " " + modeString);
    }
    else if (tokens.size() > 2)
    {
        if(tokens[2].size() == 1)
        {
            std::string m = "itkol";
            if(m.find(tokens[2][0]) != std::string::npos)
            {
                std::cout << "a" << std::endl;
                if(_channels[tokens[1]].getMode(tokens[2][0]))
                    aux->newMessage(tokens[1] + " mode + " + tokens[2]);
                else
                    aux->newMessage(tokens[1] + " mode - " + tokens[2]);
            }
        }
        if(tokens[2][0] != '+' && tokens[2][0] != '-' && tokens[2].size() > 1 )
            return(0);
        if(tokens[2].size() == 2)
        {
            if (!_channels[tokens[1]]. isOps(aux->getFd()))
            {
            	aux->newMessage(std::string("482 ") + aux->getNick() + " " + tokens[1] + " :You're not channel operator");
                return 0;
            }
            switch (tokens[2][1])
            {
            case 'i':
                _channels[tokens[1]].exMode(tokens[2][0], tokens[2][1]);
                break;
            case 't':
                _channels[tokens[1]].exMode(tokens[2][0], tokens[2][1]);
                /* Set/remove the restrictions of the TOPIC command to channel operators */
                break;
            case 'k':
                /* Set/remove the channel key (password) */
                if(tokens.size() < 4 && tokens[2][0] == '+'){
                    aux->newMessage("461 " + aux->getNick() + " MODE :Not enought arguments.");
                    return 0;
                }
                if(tokens.size() == 4){
                    _channels[tokens[1]].setPass(tokens[3]);
                }
                if(tokens.size() == 3){
                    _channels[tokens[1]].setPass("");
                }
                _channels[tokens[1]].exMode(tokens[2][0], tokens[2][1]);
                break;
            case 'o':
                /* Give/take channel operator privilege */
                if(tokens.size() < 4 && tokens[2][0] == '+'){
                    aux->newMessage("461 " + aux->getNick() + " MODE :Not enought arguments.");
                    return 0;
                }
                if(tokens.size() == 4){
                    int target = searchByFd(tokens[3]);
                    if(target != -1 && _channels[tokens[1]].isMember(target) && !_channels[tokens[1]].isOps(target) && tokens[2][0] == '+'){
                        _channels[tokens[1]].setOps(target);
                    }
                    else if(target != -1 && _channels[tokens[1]].isMember(target) && _channels[tokens[1]].isOps(target) && tokens[2][0] == '-'){
                        _channels[tokens[1]].remOps(target);
                    }
                    else if (!_channels[tokens[1]].isMember(target))
                    {
                       aux->newMessage("441 " + aux->getNick() + " " + tokens[3] + " " + tokens[1] + " :They aren't on that channel");
                       return 0;
                    }

                }
                _channels[tokens[1]].exMode(tokens[2][0], tokens[2][1]);
                break;
            case 'l':
                /* Set/remove the user limit to channel */
                if(tokens.size() < 4 && tokens[2][0] == '+'){
                    aux->newMessage("461 " + aux->getNick() + " MODE :Not enought arguments.");
                    return 0;
                }
                if(tokens.size() == 4){
                    _channels[tokens[1]].setLimit(std::atoi(tokens[3].c_str()));
                }
                _channels[tokens[1]].exMode(tokens[2][0], tokens[2][1]);
                break;
            default:
                /* code */
                break;
            }
            return (0);
        }
        return (0);
    }
    return (0);
}